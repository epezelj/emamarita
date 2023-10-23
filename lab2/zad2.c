#define CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100


typedef struct pers *Position;

typedef struct pers{

    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int birth;
    Position next_pos;


}_person;

int addBefore(Position);
Position addPers(Position);
int outputList(Position);
int addEnd(Position);
int findEl(Position, char[]);
int Delete(Position, char[]);
int chooseFun(Position);
int outputPers(Position);


int main(){

    _person Head = {.name = {0}, .surname = {0}, .birth = 0, .next_pos = 0};
    Head.next_pos = NULL;

    chooseFun(&Head);


}

int addBefore(Position Head){

    Position newPers = NULL;
    newPers = addPers(newPers);

    if(newPers!=NULL){

        newPers->next_pos = Head->next_pos;
        Head->next_pos = newPers; 

    }
    return 0;

}
int addEnd(Position Head){

    Position newPers = NULL;
    Position Pers = Head;
    newPers = addPers(newPers);

    if(Pers->next_pos!=NULL){
        while(Pers->next_pos !=NULL){

            Pers = Pers->next_pos;

        }
    }
    Pers->next_pos = newPers;
    newPers->next_pos = NULL;

    return 0;


}
int outputList(Position Pers){

    printf("Osobe su: \n");

    if(Pers->next_pos != NULL){

    while(Pers->next_pos != NULL){
    
            Pers = Pers->next_pos;

            outputPers(Pers);

        }
    }
    printf("\n");
    
    return 0;

}

int findEl(Position Pers, char surname[]){

    int true_false = 0;

    while(Pers->next_pos != NULL){
        Pers = Pers->next_pos;
        if(strcmp(Pers->surname, surname) == 0){
            printf("Trazena osoba se nalazi u polju!\n");
            outputPers(Pers);
            true_false = 1;
        }
    }
    if(true_false == 0){

        printf("\nTrazena osoba ne nalazi se u polju!\n");
    }

    printf("\n");

    return 0;



}

int Delete(Position Pers, char surname[]){

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

Position addPers(Position newPers){

    char name[MAX_LENGTH] = {0}, surname[MAX_LENGTH] = {0};
    int birth = 0;

    newPers = (Position)malloc(sizeof(Position));
    

    printf("Ime, prezime, godina rodenja: ");
    scanf("%s %s %d", name, surname, &birth);

    strcpy(newPers->name, name);
    strcpy(newPers->surname, surname);
    newPers->birth = birth;

    return newPers;

}

int chooseFun(Position Head){

    char choice;
    char surname[MAX_LENGTH];

    printf("Odaberite: \nB - dodavanje el na poc\nE - dodavanje el na kraj\nO - Ispis\nF - Pronalazenje el\nD - brisanje el\nQ - Prekid odabira\n\n");
    scanf("%c", &choice);


    do{
    if(choice == 'B')
        addBefore(Head);

    if(choice == 'E')
        addEnd(Head);

    if(choice == 'O'){
        printf("\n");
        if(Head->next_pos != NULL)
            outputList(Head);
        
        else
            printf("\nNe postoji nijedan element u listi!\n");

    }

    if(choice == 'F'){
        if(Head->next_pos != NULL){
            printf("\nUnesite prezime osobe koju trazite: ");
            scanf("%s", surname);
            printf("\n");
            findEl(Head, surname);
        }

        
        else
            printf("\nNe postoji nijedan element u listi!\n");

    }

    if(choice == 'D'){
        if(Head->next_pos != NULL){
            printf("\nUnesite prezime osobe koju zelite izbrisati: ");
            scanf("%s", surname);
            printf("\n");
            Delete(Head, surname);
        }

        
        else
            printf("\nNe postoji nijedan element u listi!\n");

    }

    printf("\nOdabrite: \nB - dodavanje el na poc\nE - dodavanje el na kraj\nO - ispis\nF - pronalazenje el\nD - brisanje el\nP - pronalazenje prethodnika\n");
    scanf("%*c%c", &choice);
    
    
    }while (choice != 'Q');
 
    return 0;
}

int outputPers(Position Pers){

    printf("%s %s %d\n", Pers->name, Pers->surname, Pers->birth);
    
    return 0;

}
