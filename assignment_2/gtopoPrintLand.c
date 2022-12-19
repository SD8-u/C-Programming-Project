/*Module to recreate gtopo file in simple text format*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "gtopoError.h"
#include "exceptionHandling.h"

/*writes a gtopo file in ascii using symbols*/
void gtopoPrint(char *fileName, gtopoModel *dem, int sea, int hill, 
int mountain){
	
	FILE *outputFile = fopen(fileName,"w");
	size_t nBytesWritten;	

	/*check file name of output file*/
	checkFileName(outputFile, fileName, dem, NULL, 0, 0);
	
	/*iterate through gtopo, writing corresponding symbols to output*/
	for(int row = 0; row < dem->height; row++){
		for(int column = 0; column < dem->width; column++){
			
			/*determine correct symbol to write*/
			char symbol;
			int value = dem->elevationData[row][column];
			if(value <= sea){
				symbol = ' ';
			}
			else if(value > sea && value <= hill){
				symbol = '.';
			}
			else if(value > hill && value <= mountain){
				symbol = '^';	
			}
			else{
				symbol = 'A';
			}
			
			/*write symbol to output file*/
			nBytesWritten = fprintf(outputFile, "%c",
			symbol);
		}
		fprintf(outputFile, "\n");
	}
	removeGtopoModel(dem);
	fclose(outputFile);			
}

int main(int argc, char **argv){
	/*check correct number of arguments*/
	checkArgCount(argc, argc, 8, argv[0], 6);

	/*determine width height*/
	checkInteger(argv[2], 0);
	int width = atoi(argv[2]);
	
	checkInteger(argv[3], 0);	
	int height = atoi(argv[3]);	

	for(int num = 5; num < 8; num++){
                checkInteger(argv[num], 1);
        }

	/*initialise gtopo model*/
	gtopoModel dem = 
	initGtopoModel(width, height, NULL, 0);
	
	/*read gtopo data from specified file*/
	gtopoRead(argv[1], &dem, NULL, 0);

	int sea = atoi(argv[5]);
	int hill = atoi(argv[6]);
	int mountain = atoi(argv[7]);

	/*call to gtopoPrint to write model in ascii*/
	gtopoPrint(argv[4], &dem, sea, hill, mountain);

	printf("PRINTED\n");	
	return 0;	
}
