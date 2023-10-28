#define CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define MAX_LINE 1024


typedef struct pers *Position;

typedef struct pers{

    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int birth;
    Position next_pos;


}_person;

int AddStart(Position);
int AddEnd(Position);
int FindPer(Position, char[]);
int PrevPers(Position, char[]);
int InputBefore(Position, char[]);
int InputAfter(Position, char[]);
int DeletePer(Position, char[]);
int DeletePerAll(Position);
int PrintList(Position);
Position AddPers(Position);
int PrintPers(Position);
int InputDat(Position);
int ReadDat();
int ChooseFun(Position);






int main(){

    _person Head = {.name = {0}, .surname = {0}, .birth = 0, .next_pos = 0};
    Head.next_pos = NULL;

    ChooseFun(&Head);
  


}

int AddStart(Position Pers){

    Position newPers = NULL;
    newPers = AddPers(newPers);

    if(newPers!=NULL){

        newPers->next_pos = Pers->next_pos;
        Pers->next_pos = newPers; 

    }
    return 0;

}
int AddEnd(Position Pers){

    Position newPers = NULL;
    newPers = AddPers(newPers);

    if(Pers->next_pos!=NULL){
        while(Pers->next_pos !=NULL){

            Pers = Pers->next_pos;

        }
    }
    Pers->next_pos = newPers;
    newPers->next_pos = NULL;

    return 0;


}

int FindPer(Position Pers, char surname[]){

    int true_false = 0;

    while(Pers->next_pos != NULL){
        Pers = Pers->next_pos;
        if(strcmp(Pers->surname, surname) == 0){
            printf("Trazena osoba se nalazi u polju!\n");
            PrintPers(Pers);
            true_false = 1;
        }
    }
    if(true_false == 0){

        printf("\nTrazena osoba ne nalazi se u polju!\n");
    }

    printf("\n");

    return 0;



}

int PrevPers(Position Pers, char surname[]){

    Position Prev = NULL;

    while(Pers != NULL && Pers->next_pos != NULL ){
        if(strcmp((Pers->next_pos)->surname, surname) == 0){
            Prev = Pers;
        
            
        }

        Pers = Pers->next_pos;
    }

    if(Prev->birth != 0){
        PrintPers(Prev);
        return 0;
    }
    
    else{
        printf("Ne postoji prethodnik");
        return -1;
    }
    
}

int InputBefore(Position Pers, char surname[]){

    Position newPers = NULL;

    newPers = AddPers(newPers);


    while(Pers != NULL && Pers->next_pos != NULL){
        if(strcmp(Pers->next_pos->surname, surname) == 0){
            newPers->next_pos = Pers->next_pos;
            Pers->next_pos = newPers;
            break;
            

        }

        Pers = Pers->next_pos;

            



    }
    return 0;

}

int InputAfter(Position Pers, char surname[]){

    Position newPers = NULL;

    newPers = AddPers(Pers);

    while(Pers != NULL){
        if(strcmp(Pers->surname, surname) == 0){
            newPers->next_pos = Pers->next_pos;
            Pers->next_pos = newPers;
            break;

        }
        Pers = Pers->next_pos;

    }
    return 0;
}



int DeletePer(Position Pers, char surname[]){

    Position temp = NULL;

    while(Pers != NULL && Pers->next_pos != NULL ){
        if(strcmp((Pers->next_pos)->surname, surname) == 0){
            temp = Pers->next_pos;
            Pers->next_pos = Pers->next_pos->next_pos;
            free(temp);

        }

        else
            Pers = Pers->next_pos;
    
    }

    return 0;



}

int DeletePerAll(Position Pers){
    
    Position temp = NULL;

    while(Pers != NULL && Pers->next_pos != NULL){
        temp = Pers->next_pos;
        Pers->next_pos = temp->next_pos;
        free(temp);

    }

    return 0;



}

int PrintList(Position Pers){

    printf("Osobe su: \n");

    //if(Pers->next_pos != NULL){

        while(Pers->next_pos != NULL){
    
            Pers = Pers->next_pos;

            PrintPers(Pers);

        }
    //}
    printf("\n");
    
    return 0;

}


Position AddPers(Position newPers){

    char name[MAX_LENGTH] = {0}, surname[MAX_LENGTH] = {0};
    int birth = 0;

    newPers = (Position)malloc(sizeof(_person));

    printf("Ime, prezime, godina rodenja: ");
    scanf("%s %s %d", name, surname, &birth);

    strcpy(newPers->name, name);
    strcpy(newPers->surname, surname);
    newPers->birth = birth;

    return newPers;

}

int PrintPers(Position Pers){

    printf("%s %s %d\n", Pers->name, Pers->surname, Pers->birth);
    
    return 0;

}


int InputDat(Position Pers) {

    FILE* filePoint = NULL;

    filePoint = fopen("people.txt", "w");

    if (!filePoint) {
        return -1;
    }
  
    while (Pers->next_pos != NULL) {

            Pers = Pers->next_pos;

            fprintf(filePoint,"%s %s %d\n", Pers->name, Pers->surname, Pers->birth);
        

    }


    fclose(filePoint);
    

    return 0;


}

int ReadDat(){

    FILE *filePoint;
    _person Pers = {.name = {0},.surname = {0}, .birth = 0, .next_pos = NULL};
    int counter = 0;
    char buffer[MAX_LINE];

    

    filePoint = fopen("people.txt", "r");

    if(!filePoint)
        return -1;

    while(1){

        fscanf(filePoint, "%s %s %d", Pers.name, Pers.surname, &Pers.birth);

        if(feof(filePoint))
            break;

        printf("%s  %s %d \n", Pers.name, Pers.surname, Pers.birth);
        
    }
        
   
    fclose(filePoint);

    return 0;
    
}


int ChooseFun(Position Head){

    char choice = {0};
    char surname[MAX_LENGTH];

    printf("Odaberite: \nB - dodavanje el na poc\nE - dodavanje el na kraj\nK - dodavanje ispred\nL - dodavnje nakon\nO - Ispis\nF - Pronalazenje el\nD - brisanje el\nA - brisanje cijele liste\nI - upis i ispis iz dat\nQ - Prekid odabira\n\n");
    scanf("%c", &choice);
    
    do{

        choice = toupper(choice);

        switch(choice){

        case 'B':
            AddStart(Head);
            break;

        case 'E':
            AddEnd(Head);
            break;

        case 'O':
            printf("\n");
            if(Head->next_pos != NULL)
                PrintList(Head);
            
            else
                printf("\nNe postoji nijedan element u listi!\n");

            break;

        case 'F':
            if(Head->next_pos != NULL){
                printf("\nUnesite prezime osobe koju trazite: ");
                scanf("%s", surname);
                printf("\n");
                FindPer(Head, surname);
            }

            
            else
                printf("\nNe postoji nijedan element u listi!\n");

            break;

        case 'D':
            if(Head->next_pos != NULL){
                printf("\nUnesite prezime osobe koju zelite izbrisati: ");
                scanf("%s", surname);
                printf("\n");
                DeletePer(Head, surname);
            }

            
            else
                printf("\nNe postoji nijedan element u listi!\n");

            break;


        case 'P':
            printf("\nUnesite prezime osobe ciji prethodnik zelite naci: ");
            scanf("%s", surname);
            printf("\n");

            PrevPers(Head, surname);

            break;

        case 'A':
            DeletePerAll(Head);
            break;

        case 'K':
            printf("\nUnesite prezime ispred kojeg ce se dodati el: ");
            scanf("%s", surname);
            printf("Surname: %s", surname);
            InputBefore(Head, surname);

            break;

        case 'L':
            printf("\nUnesite prezime nakon kojeg ce se dodati el: ");
            scanf("%s", surname);
            printf("Surname: %s", surname);
            InputAfter(Head, surname);

            break;

        case 'I':
            InputDat(Head);
            ReadDat();
            break;
        

        case 'Q':
            return 0;

        default:
            printf("Ne postoji!\n\n");
        
        }

        printf("\nOdaberite: \nB - dodavanje el na poc\nE - dodavanje el na kraj\nK - dodavanje ispred\nL - dodavnje nakon\nO - Ispis\nF - Pronalazenje el\nD - brisanje el\nA - brisanje cijele liste\nI - upis i ispis iz dat\nQ - Prekid odabira\n\n");
        scanf("%*c%c", &choice);
        
    }while(1);
    
    
        
        
    return 0;
}

