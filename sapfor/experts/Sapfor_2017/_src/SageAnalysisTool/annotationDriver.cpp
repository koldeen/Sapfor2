#include <stdio.h>
#include <string.h>
#include "sage++user.h"
#include "annotationDriver.h"


//////////////////////////////////////////////////////////////
// set of functions in the library
//////////////////////////////////////////////////////////////

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif

extern "C" {
    int initAnnotation();
    PTR_LLND Get_Define_Field(...);
    char *Get_Define_Label_Field(...);
    char *Get_Label_Field(...);
    PTR_LLND Get_ApplyTo_Field(...);
    PTR_LLND Get_ApplyToIf_Field(...);
    PTR_LLND Get_LocalVar_Field(...);
    PTR_LLND Get_Annotation_Field(...);
    char *Get_Annotation_Field_Label(...);
    char *Unparse_Annotation(...);
    char *Does_Annotation_Defines(...);
    int Get_Annotation_With_Label(...);
    int Get_Scope_Of_Annotation(...);
    PTR_LLND Does_Annotation_Apply(...);
    PTR_LLND Get_Annotation_Field_List_For_Stmt(...);
    PTR_LLND Get_Annotation_List_For_Stmt(...);
    int Get_Number_of_Annotation();
    PTR_BFND Get_Annotation_Bif(...);
    PTR_LLND Get_Annotation_Expr(...);
    char *Get_String_of_Annotation(...);
    PTR_CMNT Get_Annotation_Comment(...);
    int Is_Annotation_Defined(...);
    char *Annotation_Defines_string(...);
    int Annotation_Defines_string_Value(...);
    int isItInSection(...);    
}
extern "C" int TRACEANN;

//////////////////////////////////////////////////////////////
// Link with the Sage: maps it in sage space.
//////////////////////////////////////////////////////////////

extern SgExpression * LlndMapping(PTR_LLND pt);
extern SgStatement *BfndMapping(PTR_BFND st);

//////////////////////////////////////////////////////////////
// The interface. method of class annotations
//////////////////////////////////////////////////////////////


SgAnnotation::SgAnnotation(int ident)
{
    PTR_BFND first, last;
    SgFunctionCallExp *cal;

    if ((ident < 0) || (ident >= Get_Number_of_Annotation()))
    {
        Message("Invalid annotation", 0);
        return;
    }

    // the id of the annotation;
    id = ident;
    theannotation = LlndMapping(Get_Annotation_Expr(id));
    //the statement  it is attached on;
    stmt = BfndMapping(Get_Annotation_Bif(id));
    Get_Scope_Of_Annotation(id, &first, &last);
    scopebegin = BfndMapping(first);
    scopeend = BfndMapping(last);
    defined = Is_Annotation_Defined(id);
    thedirective = LlndMapping(Get_Annotation_Field(Get_Annotation_Expr(id)));
    directiveName = Get_Annotation_Field_Label(Get_Annotation_Expr(id));
    directiveFields = NULL;
    nbDirectiveFields = 0;
    if (cal = isSgFunctionCallExp(thedirective))
    {
        int i;
        nbDirectiveFields = cal->numberOfArgs();
        if (nbDirectiveFields)
        {
            directiveFields = new  SgExpression *[nbDirectiveFields];
#ifdef __SPF
            addToCollection(__LINE__, __FILE__, directiveFields, 2);
#endif
            for (i = 0; i < nbDirectiveFields; i++)
            {
                directiveFields[i] = cal->arg(i);
            }
        }
    }
    else
    {
        Message("Fail to recognize annotation format", 0);
    }
    next = NULL;
}


SgAnnotation::~SgAnnotation()
{
    if (directiveFields)
    {
#ifdef __SPF
        removeFromCollection(directiveFields);
#endif
        delete[] directiveFields;
    }
}


char * SgAnnotation::unparse()
{
    return Unparse_Annotation(Get_Annotation_Expr(id));
}


int SgAnnotation::applyToStatement(SgStatement *stat)
{
    SgStatement *temp;

    if (!stat)
        return 0;

    for (temp = scopebegin; temp; temp = temp->lexNext())
    {
        if (temp == stat)
            return 1;

        if (temp == scopeend)
            break;
    }
    return 0;
}



////////////////////////////////////////////////////////////////////////
// non method functions to get the annotation
///////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// create the list of annotations that applies to a statements
// only the defined one
/////////////////////////////////////////////////////////////


SgAnnotation *
getTheAnnotationThatApply(SgStatement *stmt, char *kind)
{
    int i;
    PTR_BFND first, last;
    SgAnnotation *listann = NULL;
    SgAnnotation *lastann = NULL;
    PTR_BFND bif;

    if (!stmt)
        return NULL;
    bif = stmt->thebif;

    for (i = 0; i < Get_Number_of_Annotation(); i++)
    {
        if (Is_Annotation_Defined(i))
        {
            if (kind)
            {
                if (Get_Annotation_Field_Label(Get_Annotation_Expr(i)) &&
                    (strcmp(Get_Annotation_Field_Label(Get_Annotation_Expr(i)), kind) == 0))
                {
                    if (Get_Scope_Of_Annotation(i, &first, &last))
                    {
                        if (isItInSection(first, last, bif))
                        {
                            if (!listann)
                            {
                                listann = new SgAnnotation(i);
#ifdef __SPF
                                addToCollection(__LINE__, __FILE__, listann, 1);
#endif
                                lastann = listann;
                            }
                            else
                            {
                                lastann->next = new SgAnnotation(i);
#ifdef __SPF
                                addToCollection(__LINE__, __FILE__, listann->next, 1);
#endif
                                lastann = lastann->next;
                            }
                        }
                    }
                }
            }
            else
            {
                if (Get_Scope_Of_Annotation(i, &first, &last))
                {
                    if (isItInSection(first, last, bif))
                    {
                        if (!listann)
                        {
                            listann = new SgAnnotation(i);
#ifdef __SPF
                            addToCollection(__LINE__, __FILE__, listann, 1);
#endif
                            lastann = listann;
                        }
                        else
                        {
                            lastann->next = new SgAnnotation(i);
#ifdef __SPF
                            addToCollection(__LINE__, __FILE__, listann->next, 1);
#endif
                            lastann = lastann->next;
                        }
                    }
                }
            }
        }
    }
    return listann;
}



SgAnnotation *
getTheAnnotationWithString(char *kind)
{
    int i;
    PTR_BFND first, last;
    SgAnnotation *listann = NULL;
    SgAnnotation *lastann = NULL;
    PTR_BFND bif;


    for (i = 0; i < Get_Number_of_Annotation(); i++)
    {
        if (Is_Annotation_Defined(i))
        {
            if (kind)
            {
                if (Get_Annotation_Field_Label(Get_Annotation_Expr(i)) &&
                    (strncmp(Get_Annotation_Field_Label(Get_Annotation_Expr(i)),
                        kind, strlen(kind)) == 0))
                    if (!listann)
                    {
                        listann = new SgAnnotation(i);
#ifdef __SPF
                        addToCollection(__LINE__, __FILE__, listann, 1);
#endif
                        lastann = listann;
                    }
                    else
                    {
                        lastann->next = new SgAnnotation(i);
#ifdef __SPF
                        addToCollection(__LINE__, __FILE__, listann->next, 1);
#endif
                        lastann = lastann->next;
                    }
            }
        }
    }
    return listann;
}

int
isAnnotationWithString(SgStatement *stmt, char *kind, int len)
{
    int i;
    PTR_BFND first, last;
    SgAnnotation *listann = NULL;
    SgAnnotation *lastann = NULL;
    PTR_BFND bif;

    if (!stmt)
        return 0;
    bif = stmt->thebif;

    for (i = 0; i < Get_Number_of_Annotation(); i++)
    {
        if (Is_Annotation_Defined(i))
        {
            if (kind)
            {
                if (Get_Annotation_Field_Label(Get_Annotation_Expr(i)) &&
                    (strncmp(Get_Annotation_Field_Label(Get_Annotation_Expr(i)),
                        kind, len) == 0))
                {
                    if (Get_Scope_Of_Annotation(i, &first, &last))
                    {
                        if (isItInSection(first, last, bif))
                            return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void initAnnotationSystem(int printann)
{
    int i;
    SgExpression *exp;
    SgStatement *stmt;
    if (printann)
    {
        TRACEANN = 1;
    }
    initAnnotation();
    // add also the annotation expression for the garbage collection  attributes;

    for (i = 0; i < Get_Number_of_Annotation(); i++)
    {
        exp = LlndMapping(Get_Annotation_Expr(i));
        stmt = BfndMapping(Get_Annotation_Bif(i));
        if (stmt && exp)
        {
            stmt->addAttribute(ANNOTATION_EXPR_ATTRIBUTE, (void *)exp, 0);
        }
    }

}
