#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 1024

typedef struct _article *PositionArticle;
typedef struct _article{

    char article[MAX_LENGTH];
    int amount;
    float price;
    PositionArticle nextArticle;

}Article;

typedef struct _receipt *PositionReceipt;
typedef struct _receipt{
    
    int year, month, day;
    PositionReceipt nextReceipt;
    Article ArticleHead;

}Receipt;

int ReadFile(PositionReceipt);
PositionReceipt ReceiptDate(int, int, int);
int ReadReceipt(char[], PositionReceipt);
int SortArticles(PositionArticle, char[], int, float);
int SortReceipts(PositionReceipt, PositionReceipt);
int DateSort(PositionReceipt, PositionReceipt);
int ArticleSum(PositionArticle, PositionArticle);
int ArticleMerge(PositionArticle, PositionArticle);
int Print(PositionReceipt);

int main()
{
    Receipt HeadReceipt = {.year = 0, .month = 0, .day = 0, .nextReceipt = NULL, .ArticleHead = {.article = {0}, .amount = 0, .price = 0.0, .nextArticle = NULL}};
    ReadFile(&HeadReceipt);
}


int ReadFile(PositionReceipt HeadReceipt){

    FILE *filepointer = NULL;
    char receipts[MAX_LENGTH] = {0}, line[MAX_LENGTH];
    int value = 0, bytes = 0, counter = 0;

    filepointer = fopen("racuni.txt", "r");

    if(!filepointer)
        return -1;

    while(fscanf(filepointer, "%s", receipts) == 1)
    {  
        //printf("\n%s", receipts);
        
        ReadReceipt(receipts, HeadReceipt);
        
    }
    if(!feof(filepointer))
        return -1;

    fclose(filepointer);

    Print(HeadReceipt);

}

int ReadReceipt(char receipts[], PositionReceipt HeadReceipt){

    FILE *filepointer_receipt = NULL;
    int year = 0, month = 0, day = 0, amount = 0, value = 0, bytes = 0;
    float price = 0.0;
    char article[MAX_LENGTH] = {0}, receipt[MAX_LENGTH];
    PositionReceipt newReceipt;

    filepointer_receipt = fopen(receipts, "r");

    if(!filepointer_receipt)
        return -1;

    fscanf(filepointer_receipt, "%d-%d-%d", &year, &month, &day);
    printf("\n%d-%d-%d\n", year, month, day);

    while(fscanf(filepointer_receipt, "%s %d %f", article, &amount, &price) == 3)
    {
        //printf("%s %d %.1f\n",article, amount, price);
        newReceipt = ReceiptDate(year, month, day);
        if(!newReceipt)
            return -1;

        SortArticles(newReceipt, article, amount, price);

    }
    if(!feof(filepointer_receipt))
        return -1;
        
    SortReceipts(HeadReceipt, newReceipt);
    

    fclose(filepointer_receipt);
}

PositionReceipt ReceiptDate(int year, int mont, int day){

    PositionReceipt newReceipt = (PositionReceipt)malloc(sizeof(Receipt));

    if(!newReceipt)
        return NULL;

    newReceipt->year = year;
    newReceipt->month = month;
    newReceipt->day = day;

    return newReceipt;

}

int SortArticles(PositionArticle newReceipt, char article[], int amount, float price){

    PositionArticle newArticle = (PositionArticle)malloc(sizeof(Article));
    PositionArticle currentArticle = &(newReceipt->ArticleHead);

    if(!newArticle)
        return -1;  

    strcpy(newArticle->article, article);
    newArticle->amount = amount;
    newArticle->price = price;

    while(currentArticle->nextArticle != NULL && strcmp(currentArticle->nextArticle->article, newArticle->article) <= 0)
        currentArticle = currentArticle->nextArticle;

    if(currentArticle->nextArticle != NULL && strcmp(currentArticle->nextArticle->article, newArticle->article) == 0)
        ArticleSum(currentArticle->nextArticle, newArticle);

    else 
    {
        newArticle->nextArticle = currentArticle->nextArticle;
        currentArticle->nextArticle = newArticle;

    }

}
int ArticleSum(PositionArticle currentArticle, PositionArticle newArticle){

    currentArticle->amount += newArticle->amount;
    currentArticle->price += newArticle->price;

    return 0;
}

int SortReceipts(PositionReceipt HeadReceipt, PositionReceipt newReceipt){

    PositionReceipt currentReceipt = HeadReceipt;

    while(currentReceipt->nextReceipt != NULL && DateSort(currentReceipt->nextReceipt, newReceipt) == 2)
        currentReceipt = currentReceipt->nextReceipt;
    
    if(currentReceipt->nextReceipt != NULL && DateSort(currentReceipt->nextReceipt, newReceipt) == 1)
    {
        newReceipt->nextReceipt = HeadReceipt->nextReceipt;
        HeadReceipt->nextReceipt = newReceipt;

    }

    else if(currentReceipt->nextReceipt != NULL && DateSort(currentReceipt->nextReceipt, newReceipt) == 3)
    {
        ArticleMerge(currentReceipt->nextReceipt->ArticleHead, newReceipt->ArticleHead);

    }
    else{

        newReceipt->nextReceipt = currentReceipt->nextReceipt;
        currentReceipt->nextReceipt = newReceipt;

    }


}

int ArticleMerge(PositionArticle ArticleHead, PositionArticle newRecArtHead){

    PositionArticle currentArticle = ArticleHead;
    PositionArticle newCurrArticel = newRecArtHead;
    PositionArticle temp;


    while(currentArticle != NULL && currentArticle->nextArticle != NULL)
    {
        while(newCurrArticel != NULL && newCurrArticel->nextArticle != NULL)
        {
            if(strcmp(currentArticle->nextArticle->article, newCurrArticel->nextArticle->article) == 0)
            {
                ArticleSum(currentArticle, newCurrArticel);
                temp = newCurrArticel->nextArticle;
                newCurrArticel->nextArticle = newCurrArticel->nextArticle->nextArticle;
                free(temp);

                

            }

            newCurrArticel = newCurrArticel->nextArticle;
        }
        currentArticle = currentArticle->nextArticle;
        newCurrArticel = newRecArtHead->nextArticle;
    }
    newCurrArticel = newRecArtHead;
    while(newCurrArticel != NULL && newCurrArticel->nextArticle != NULL)
    {
        SortArticles(ArticleHead, newCurrArticel->nextArticle->article, newCurrArticel->nextArticle->amount, newCurrArticel->nextArticle->price);
        temp = newCurrArticel->nextArticle;
        newCurrArticel->nextArticle= newCurrArticel->nextArticle->nextArticle;
        free(temp);

        newCurrArticel = newCurrArticel->nextArticle;
    }

}

int DateSort(PositionReceipt currentReceipt, PositionReceipt newReceipt){

    if(currentReceipt->year > newReceipt->year)
        return 1;

    if(currentReceipt->year < newReceipt->year)
        return 2;
    
    else 
    {
        if(currentReceipt->month > newReceipt->month)
            return 1;

        if(currentReceipt->month < newReceipt->month)
            return 2;

        else{
            
            if(currentReceipt->day > newReceipt->day)
                return 1;
            
            if(currentReceipt->day < newReceipt->day)
                return 2;
            
            else 
                return 3;
        }
    }
}

int Print(PositionReceipt HeadReceipt)
{
    PositionReceipt currentReceipt = HeadReceipt->nextReceipt;
    PositionArticle currentArticle = HeadReceipt->ArticleHead;
    currentArticle = currentArticle->nextArticle;

    while(currentReceipt != NULL)
    {
        printf("%d-%d-%d\n", currentReceipt->year, currentReceipt->month, currentReceipt->day);
        while(currentArticle != NULL)
        {
            printf("%s %d %f\n", currentArticle->article, currentArticle->amount, currentArticle->price);
            currentArticle = currentArticle->nextArticle;
        }


    }


}
