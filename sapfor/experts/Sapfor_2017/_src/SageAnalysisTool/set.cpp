#include <stdio.h>
#include <malloc.h>
#include "sage++user.h"
#include "definesValues.h"
#include "set.h"

#ifdef __SPF
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);
extern "C" void removeFromCollection(void *pointer);
#endif

Set::Set(int(*feq)(void *e1, void *e2),
    void *(*fcomb)(void *e1, void *e2),
    void(*fp)(void *e1))
{

    data = NULL;
    nbelement = 0;
    nballocated = 0;
    equal = feq;
    combine = fcomb;
    printEl = fp;
    deallocelem = 0;
}

void Set::printSet()
{
    int i;
    if (!printEl)
    {
        Message("Function printEl not given", 0);
        return;
    }
    if (!this->size())
        printf("Empty set\n");
    else
    {
        for (i = 0; i < this->size(); i++)
        {
            (*printEl)(getElement(i));
        }
        printf("\n");
    }
}

void Set::interSet(Set *s1, Set *s2)
{
    int i, j;
    int trouve;
    void *e1, *e2;
    if (!equal)
        return;
    if (!s1 || !s2)
        return;
    if (!equal)
    {
        Message("Function Equal not given", 0);
        return;
    }
    for (i = 0; i < s1->size(); i++)
    {
        e1 = s1->getElement(i);
        if (e1)
        {
            trouve = 0;
            for (j = 0; j < s2->size(); j++)
            {
                e2 = s2->getElement(j);
                if ((*equal)(e1, e2))
                {
                    trouve = 1;
                    break;
                }
            }
            if (trouve)
                this->addElement(e1);
        }
    }
}

void Set::unionSet(Set *s1)
{
    int i, j;
    int trouve;
    void *e1, *e2;
    int initsize;
    int initsize2;

    if (!s1)
    {
        return;
    }
    if (!equal)
    {
        Message("Function Equal not given", 0);
        return;
    }
    initsize = s1->size();
    initsize2 = this->size();
    for (i = 0; i < initsize; i++)
    {
        e1 = s1->getElement(i);
        if (e1)
        {
            trouve = 0;
            for (j = 0; j < initsize2; j++)
            {
                e2 = this->getElement(j);
                if ((*equal)(e1, e2))
                {
                    trouve = 1;
                    break;
                }
            }
            if (!trouve)
                this->addElement(e1);
        }
    }
}
int Set::equalSet(Set *s1)
{
    int i, j;
    int trouve;
    void *e1, *e2;
    if (!s1)
        return 0;

    if (!equal)
    {
        Message("Function Equal not given", 0);
        return 0;
    }
    if (this->size() != s1->size())
        return 0;

    for (i = 0; i < size(); i++)
    {
        e1 = getElement(i);
        if (e1)
        {
            trouve = 0;
            for (j = 0; j < s1->size(); j++)
            {
                e2 = s1->getElement(j);
                if ((*equal)(e1, e2))
                {
                    trouve = 1;
                    break;
                }
            }
            if (!trouve)
                return 0;
        }
    }
    return 1;
}

int Set::isInSet(void *e1)
{
    int i, j;
    int trouve;
    void *e2;
    if (!e1)
        return 0;
    if (!equal)
    {
        Message("Function Equal not given", 0);
        return 0;
    }
    for (i = 0; i < size(); i++)
    {
        e2 = getElement(i);
        if (e1)
        {
            if ((*equal)(e1, e2))
            {
                return 1;
            }
        }
    }
    return 0;
}

void Set::diffSet(Set *s1, Set *s2)
{
    int i, j;
    int trouve;
    void *e1, *e2;
    int initsize;
    if (!s2)
    {
        if (s1)
        {
            for (i = 1; i < s1->size(); i++)
            {
                e1 = s1->getElement(i);
                this->addElement(e1);
            }
        }
        return;
    }
    if (!equal)
    {
        Message("Function Equal not given", 0);
        return;
    }
    initsize = s1->size();
    for (i = 0; i < initsize; i++)
    {
        e1 = s1->getElement(i);
        if (e1)
        {
            trouve = 0;
            for (j = 1; j < s2->size(); j++)
            {
                e2 = s2->getElement(j);
                if ((*equal)(e1, e2))
                {
                    trouve = 1;
                    break;
                }
            }
            if (!trouve)
                this->addElement(e1);
        }
    }
}




void Set::Reallocatedata()
{
    int i;
    void **pt;

    pt = new void *[nballocated + ALLOCATECHUNKSET];

#ifdef __SPF
    addToCollection(__LINE__, __FILE__, pt, 2);
#endif
    for (i = 0; i < nballocated + ALLOCATECHUNKSET; i++)
        pt[i] = NULL;

    for (i = 0; i < nballocated; i++)
        pt[i] = data[i];

    if (nballocated)
    {
#ifdef __SPF
        removeFromCollection(data);
#endif
        delete[] data;
    }
    data = pt;
    nballocated = nballocated + ALLOCATECHUNKSET;
}

void Set::addElement(void *el)
{
    if (!el)
        return;
    // should check if already here
    if (nbelement >= MAXELEMENT)
    {
        Message("Too many element in set", 0);
        return;
    }
    while (nballocated <= (nbelement + 1))
    {
        Reallocatedata();
    }
    data[nbelement] = el;
    nbelement++;
}



Set *Set::compact()
{
    int i, k;
    int trouve;
    Set *newset;
    if (!equal)
    {
        Message("Function Equal not given", 0);
        return NULL;
    }
    // look at duplicate elements, and combine (to see later) if necessary
    newset = new Set(equal, combine, printEl);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, newset, 1);
#endif
    for (i = 0; i < this->size(); i++)
    {
        trouve = 0;
        for (k = 0; k < newset->size(); k++)
        {
            if ((*equal)(data[i], newset->data[k]))
            {
                trouve = 1;
                break;
            }
        }
        if (!trouve && data[i])
        {
            newset->addElement(data[i]);
        }
    }
    return newset;
}



Set *Set::combineSet()
{
    int i, j, inisize;
    int change;
    Set *newset, *temp;
    void *pt;
    int step = 0;
    if (!combine)
    {
        Message("Function Combine not given", 0);
        return NULL;
    }
    temp = this->copy();
    change = 1;

    while (change)
    {
        step++;
        change = 0;
        inisize = temp->size();
        for (i = 0; i < inisize; i++)
        {
            for (j = i + 1; j < inisize; j++)
            {
                if (temp->getElement(i) && temp->getElement(j))
                {
                    pt = combine(temp->getElement(i), temp->getElement(j));
                    if (pt)
                    {
                        temp->addElement(pt);
                        change = 1;
                        temp->rmElement(j);
                        temp->rmElement(i);
                    }
                    else
                        temp->addElement(pt);
                }
            }
        }
        if (step > MAXITDATAFLOW)
        {
            Message("Combine set is Looping", 0);
            break;
        }
    }
    ///////////////////////////////
    // PAS DE DESALLOCATION     //
   ///////////////////////////////
   // newset = temp;
   // temp = temp->compact();
   //  if (newset)
   //   delete newset;
    return temp;
}

Set *Set::copy()
{
    int i, k;
    Set *newset;
    newset = new Set(equal, combine, printEl);
#ifdef __SPF
    addToCollection(__LINE__, __FILE__, newset, 1);
#endif
    for (i = 0; i < this->size(); i++)
    {
        if (data[i])
            newset->addElement(data[i]);
    }
    return newset;
}

void *Set::getElement(int i) const
{
    void *pt;
    if ((i < 0) || (i >= nbelement))
        return NULL;
    pt = data[i];
    return pt;
}

void *Set::rmElement(int i)
{
    void *pt;
    if ((i < 0) || (i >= nbelement))
        return NULL;
    pt = data[i];
    data[i] = NULL;
    return pt;
}

Set::~Set()
{
    int i;
    if (data)
    {
        if (deallocelem)
        {
            for (i = 0; i < nbelement; i++)
            {
#ifdef __SPF
                removeFromCollection(data[i]);
#endif
                delete [](char*)data[i];
            }
        }
#ifdef __SPF
        removeFromCollection(data);
#endif
        delete []data;
    }
}
