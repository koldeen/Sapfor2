#pragma once
///////////////////////////////////////////////////////////////////
// interface to the annotations
///////////////////////////////////////////////////////////////////



class SgAnnotation
{
public:
    // the id of the annotation;
    int id;
    // the annotation itself;
    SgExpression *theannotation;
    //the statement  it is attached on;
    SgStatement *stmt;
    SgStatement *scopebegin;
    SgStatement *scopeend;
    int defined;
    SgExpression *thedirective;
    char *directiveName;
    // pointer to the next annotation for a statement;
    SgAnnotation *next;
    SgAnnotation(int id);
    ~SgAnnotation();
    char * unparse();
    int applyToStatement(SgStatement *stat);
    SgExpression **directiveFields;
    int nbDirectiveFields;
};

