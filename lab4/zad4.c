#define CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

typedef struct el *Element;
typedef struct el{
    int coeff;
    int pot;
    Element next_pos;
}_element;

int SumPol(Element, Element, Element);
int MultiplyPol(Element, Element, Element);
int ReadFile(Element, Element);
int Seperate(char *, Element);
Element AddEl(Element, int, int);
int InputSort(Element, Element);
int AddEnd(Element, Element);
int DeleteEl(Element);
int FreeAll(Element, Element);
int PrintPol(Element);

int main()
{
    _element Head_pol1 = {.coeff = 0, .pot = 0, .next_pos = NULL};
    _element Head_pol2 = {.coeff = 0, .pot = 0, .next_pos = NULL};
    _element Head_multiplyPol = {.coeff = 0, .pot = 0, .next_pos = NULL};
    _element Head_sumPol = {.coeff = 0, .pot = 0, .next_pos = NULL};

    ReadFile(&Head_pol1, &Head_pol2);
    PrintPol(&Head_pol1);
    printf("\n");
    PrintPol(&Head_pol2);
    MultiplyPol(&Head_pol1, &Head_pol2, &Head_multiplyPol);
    printf("\n");
    PrintPol(&Head_multiplyPol);
    printf("\n");
    SumPol(&Head_pol1, &Head_pol2, &Head_sumPol);
    PrintPol(&Head_sumPol);
    //FreeAll(&Head_pol1, &Head_pol2);

    return 0;
}

int SumPol(Element Head_pol1, Element Head_pol2, Element Head_sumPol)
{
    Element current_pol1 = Head_pol1->next_pos;
    Element current_pol2 = Head_pol2->next_pos;
    int sumCoeff = 0;

    while(current_pol1 != 0 && current_pol2 != 0)
    {
        if(current_pol1->pot == current_pol2->pot)
        {
            sumCoeff = current_pol1->coeff + current_pol2->coeff;
            if(sumCoeff != 0)
                AddEl(Head_sumPol, sumCoeff, current_pol1->pot);
            
                current_pol1 = current_pol1->next_pos;
                current_pol2 = current_pol2->next_pos; 
        }
        else if(current_pol1->pot > current_pol2->pot)
        {
            AddEl(Head_sumPol, current_pol1->coeff, current_pol1->pot);
            current_pol1 = current_pol1->next_pos;
        }
        else
        {
            AddEl(Head_sumPol, current_pol2->coeff, current_pol2->pot);
            current_pol2 = current_pol2->next_pos;
        } 
    }
    while(current_pol1 != 0)
    {
        AddEl(Head_sumPol, current_pol1->coeff, current_pol1->pot);
        current_pol1 = current_pol1->next_pos;
    }
    while(current_pol2 != 0)
    {
        AddEl(Head_sumPol, current_pol2->coeff, current_pol2->pot);
        current_pol2 = current_pol2->next_pos;
    }

    return 0;
}   
    
int MultiplyPol(Element Head_pol1, Element Head_pol2, Element Head_multiplyPol)
{
    Element current_pol1 = Head_pol1->next_pos;
    Element current_pol2 = Head_pol2->next_pos;
    Element newElement = NULL;
    int multiplyCoeff = 0, multiplyPot = 0;

    while(current_pol1 != NULL)
    {
        while(current_pol2 !=NULL)
        {
            multiplyCoeff = current_pol1->coeff * current_pol2->coeff;
            multiplyPot = current_pol1->pot + current_pol2->pot;
            newElement = AddEl(Head_multiplyPol, multiplyCoeff, multiplyPot);

            current_pol2 = current_pol2->next_pos;
        }
        current_pol1 = current_pol1->next_pos;
        current_pol2 = Head_pol2->next_pos;
    }

    return 0;
}

int ReadFile(Element Head_pol1, Element Head_pol2)
{
    FILE *filepointer = NULL;
    char line[MAX_LINE];
    int coeff = 0, pot = 0;

    filepointer = fopen("polinomi.txt", "r");

    if(!filepointer)
        return -1;

    fgets(line, MAX_LINE, filepointer);
    Seperate(line, Head_pol1);

    fgets(line, MAX_LINE, filepointer);
    Seperate(line, Head_pol2);

    printf("\n");

    fclose(filepointer);
    
    return 0;
}

int Seperate(char *line, Element Head)
{
    int coeff = 0, pot = 0, value = 0, bytes = 0, counter = 0;

    while(strlen(line+counter)>0)
    {
        value = sscanf(line+counter, "%dx^%d %n", &coeff, &pot, &bytes);
        counter+=bytes;

        if(value != 2)
            return -1;

        if(value == 2)
            AddEl(Head, coeff, pot);
    }

    return 0;
}

Element AddEl(Element Head, int coeff, int pot)
{
    Element newElement = NULL;
    newElement = (Element)malloc(sizeof(_element));
    if(!newElement)
        return NULL;
    
    newElement->coeff = coeff;
    newElement->pot = pot;

    InputSort(Head, newElement);

    return newElement;
}


int InputSort(Element Head, Element newElement)
{
    Element current = Head;

    if(!newElement)
        return -1;

    while(current->next_pos != NULL && current->next_pos->pot > newElement->pot)
            current = current->next_pos;

    if(current->next_pos != NULL)
    {
        if(current->next_pos->pot < newElement->pot)
            AddEnd(current, newElement);
            
        else
        {
            current->next_pos->coeff += newElement->coeff;
            free(newElement);

            if (current->next_pos->coeff == 0)
                DeleteEl(Head);
        }
    }
    else
        AddEnd(current, newElement);
        
    return 0;
}

int AddEnd(Element current, Element newElement)
{
    if (current->next_pos == NULL)
    {
        newElement->next_pos = NULL;
        current->next_pos  = newElement;   
    }
    else
    {
        newElement->next_pos = current->next_pos;
        current->next_pos = newElement;
    }

    return 0;
}

int DeleteEl(Element Head){

    Element current = Head;
    Element temp = NULL;

    while(current != NULL && current->next_pos != NULL && current->next_pos->coeff!=0)
        current = current->next_pos;

    if(current->next_pos->coeff == 0)
    {       
        temp = current->next_pos;
        current->next_pos = current->next_pos->next_pos;
        free(temp);
    }

    return 0;
}

int FreeAll(Element Head_pol1, Element Head_pol2)
{
    Element current_pol1 = Head_pol1->next_pos;
    Element current_pol2 = Head_pol2->next_pos;
    Element temp = NULL;

    while(current_pol1 != NULL)
    {
        temp = current_pol1;
        current_pol1 = current_pol1->next_pos;
        free(temp); 
    }
    while(current_pol2 != NULL)
    {
        temp = current_pol2;
        current_pol2 = current_pol2->next_pos;
        free(temp);
    }

    return 0;
}

int PrintPol(Element Head)
{
    Element current = Head->next_pos;
    while(current != NULL)
    {
        printf(" %dx^%d ",current->coeff, current->pot);
        current = current->next_pos;
    }

    return 0;

}
