/*Module to reduce pgm image by specified integer factor*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "gtopoError.h"
#include "exceptionHandling.h"
#include "reduceUtilities.h"

int main(int argc, char **argv){
	
	/*check correct number of arguments (6)*/
	checkArgCount(argc, argc, 6, argv[0], 3);

	/*determine height and width*/
	checkInteger(argv[2], 0);
	int width = atoi(argv[2]);
	
	checkInteger(argv[3], 0);
	int height = atoi(argv[3]);

	/*check data type of integer factor*/
        checkInteger(argv[4], 0);
        int n = atoi(argv[4]);
	
	/*initialise pgm image*/
	gtopoModel dem = 
	initGtopoModel(width, height, NULL, 0);

	/*read pgm image using specified file*/
	gtopoRead(argv[1], &dem, NULL, 0);

	/*create reduced image by calling to reduce function*/
	gtopoModel reducedDem = reduceGtopo(&dem, n);

	/*cleanUp*/
	removeGtopoModel(&dem);

	/*write pgm to file*/
	gtopoWrite(argv[5], &reducedDem, NULL, 0, 0);

	/*print "REDUCED" if no errors occured*/	
	printf("REDUCED\n");

	return 0; 	
}
