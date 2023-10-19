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



int numRows(FILE *filePointer){

	int noRows = 0;
	char buffer[MAX_LINE];

	while (!feof(filePointer)) {
		fgets(buffer, MAX_LINE, filePointer);
		noRows++;

	}
	return noRows;
}


void Read_struct(FILE *filePointer, _student *pointerStudenti, int noRows){

	int counter = 0;

	while(counter!=noRows){
		fscanf(filePointer, "%s %s %lf", (pointerStudenti+counter)->name, (pointerStudenti+counter)->surname, &((pointerStudenti+counter)->points));

		counter++;
	}

}


double Max(FILE *filePointer, _student *pointerStudenti, int noRows){

	double max_points = 0;

	for(int counter = 0; counter < noRows; counter++){

		if(((pointerStudenti+counter)->points) > max_points){
			max_points=(pointerStudenti+counter)->points;

		}
	}
	return max_points;


}

void Output(_student *pointerStudenti, int noRows, int max_points){

	int counter = 0;

	printf("%-6s %-8s %-8s %s\n", "IME", "PREZIME", "APS.BOD.", "REL.BOD.");

	while(counter!=noRows){
		printf("%-6s %-8s %-8.2lf %.2lf\n", (pointerStudenti+counter)->name, (pointerStudenti+counter)->surname, (pointerStudenti+counter)->points, (pointerStudenti+counter)->points/max_points*100);
		counter++;
	}
	
}


int main() {

	int noRows = 0, counter = 0;
	FILE *filePointer = NULL;
	char buffer[MAX_LINE] = {0};
	_student *pointerStudenti = NULL;
	double max_points = 0;


	filePointer = fopen("imena.txt", "r");
	

	if (!filePointer) {
		printf("file is not openned!\n");
		return -1;
	}

	noRows = numRows(filePointer);

	rewind(filePointer);

	pointerStudenti = (_student *)malloc(sizeof(_student)*noRows);
	Read_struct(filePointer, pointerStudenti, noRows);
	max_points = Max(filePointer, pointerStudenti, noRows);
	Output(pointerStudenti, noRows, max_points);


	fclose(filePointer);
	
	return 0;

}
	