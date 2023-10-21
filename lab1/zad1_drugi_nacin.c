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


int numRows();
int Read_struct( _student *, int);
double Max( _student *, int);
int Output(_student *, int, int);



int main() {

	
	char buffer[MAX_LINE] = {0};
	_student *pointerStudenti = NULL;
	double max_points = 0;
	int noRows = 0;


	noRows = numRows();
	
	pointerStudenti = (_student *)malloc(sizeof(_student)*noRows);

	Read_struct(pointerStudenti, noRows);
	max_points = Max(pointerStudenti, noRows);
	Output(pointerStudenti, noRows, max_points);

	free(pointerStudenti);

	return 0;

}


int numRows(){

	FILE *filePointer = NULL;
	int noRows = 0, counter = 0;
	char buffer[MAX_LINE] = {0};

	filePointer = fopen("imena.txt", "r");
	

	if (!filePointer) {
		printf("file is not openned!\n");
		return -1;
	}

	while (!feof(filePointer)) {
		fgets(buffer, MAX_LINE, filePointer);
		noRows++;

	}
	fclose(filePointer);

	return noRows;
}


int Read_struct( _student *pointerStudenti, int noRows){

	FILE *filePointer = NULL;
	int counter = 0;

	filePointer = fopen("imena.txt", "r");
	

	if (!filePointer) {
		printf("file is not openned!\n");
		return -1;
	}

	while(counter!=noRows){

		fscanf(filePointer, "%s %s %lf", (pointerStudenti+counter)->name, (pointerStudenti+counter)->surname, &((pointerStudenti+counter)->points));

		counter++;
	}

	fclose(filePointer);

	return 0;

}


double Max( _student *pointerStudenti, int noRows){

	FILE *filePointer = NULL;
	int counter = 0;
	double max_points = 0;

	filePointer = fopen("imena.txt", "r");
	

	if (!filePointer) {
		printf("file is not openned!\n");
		return -1;
	}

	for(int counter = 0; counter < noRows; counter++){

		if(((pointerStudenti+counter)->points) > max_points){
			max_points=(pointerStudenti+counter)->points;

		}
	}
	return max_points;

	fclose(filePointer);

}


int Output(_student *pointerStudenti, int noRows, int max_points){

	FILE *filePointer = NULL;
	int counter = 0;

	filePointer = fopen("imena.txt", "r");
	

	if (!filePointer) {
		printf("file is not openned!\n");
		return -1;
	}

	printf("%-6s %-8s %-8s %s\n", "IME", "PREZIME", "APS.BOD.", "REL.BOD.");

	while(counter!=noRows){
		printf("%-6s %-8s %-8.2lf %.2lf\n", (pointerStudenti+counter)->name, (pointerStudenti+counter)->surname, (pointerStudenti+counter)->points, (pointerStudenti+counter)->points/max_points*100);
		counter++;
	}

	fclose(filePointer);

	return 0;
	
}

	