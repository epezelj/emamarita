#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 50
#define MAX_LINE 1024

typedef struct {

	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;


} _student;

int main() {

	int noRows = 0, counter = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE];
	_student *pointerStudenti;
	double max_points = 0;


	filePointer = fopen("imena.txt", "r");
	

	if (!filePointer) {
		printf("file is not openned!\n");
		return -1;
	}

	while (!feof(filePointer)) {
		fgets(buffer, 1024, filePointer);
		noRows++;

	}

	rewind(filePointer);
	pointerStudenti = (_student *)malloc(sizeof(_student));


	while(counter!=noRows){
		fscanf(filePointer, "%s %s %lf", (pointerStudenti+counter)->name, (pointerStudenti+counter)->surname, &(pointerStudenti+counter)->points);

		if(((pointerStudenti+counter)->points) > max_points){
			max_points=(pointerStudenti+counter)->points;

		}
		counter++;
	}

	counter = 0;
	rewind(filePointer);
	printf("%-6s %-8s %-8s %s\n", "IME", "PREZIME", "APS.BOD.", "REL.BOD.");

	while(counter!=noRows){
		printf("%-6s %-8s %-8.2lf %.2lf\n", (pointerStudenti+counter)->name, (pointerStudenti+counter)->surname, (pointerStudenti+counter)->points, (pointerStudenti+counter)->points/max_points*100);
		counter++;
	}

}
	