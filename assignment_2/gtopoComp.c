/*Module to compare gtopo models*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "exceptionHandling.h"
#include "gtopoError.h"

/*compares equivalence of two given gtopo files*/
int compareGtopo(gtopoModel dem1, gtopoModel dem2){

	/*check whether each elevation value of each model is
  	equivalent*/
	for(int row = 0; row < dem1.height; row++){
		for(int column = 0; column < dem1.width; column++){
				
			/*if not equal, return false (0)*/
			if(dem1.elevationData[row][column] != dem2.
			elevationData[row][column]){
				return 0;
			}	
		}		
	}	

	/*return true if no values were different*/
	return 1;
}


int main(int argc, char **argv){
	
	/*check correct number of arguments*/
	checkArgCount(argc, argc, 5, argv[0], 2);

	/*determine width and height*/
	checkInteger(argv[2], 0);
	int width = atoi(argv[2]);	

	checkInteger(argv[3], 0);
	int height = atoi(argv[3]);
	
	/*initialise gtopo models in memory*/
	gtopoModel dem1 = 
	initGtopoModel(width, height, NULL, 0);

	gtopoModel dem2 = 
	initGtopoModel(width, height, &dem1, 1);

	/*read data of each gtopo model from
 	specified file*/
	gtopoRead(argv[1], &dem1, &dem2, 1);

	gtopoRead(argv[4], &dem2, &dem1, 1);

	/*determine whether they are
	equivalent*/	
	int equal = compareGtopo(dem1, dem2);
	if(equal){
		printf("IDENTICAL\n");
	}
	else{
		printf("DIFFERENT\n");
	}

	/*cleanUp*/
	removeGtopoModel(&dem1);
	removeGtopoModel(&dem2);
	return 0;
}
