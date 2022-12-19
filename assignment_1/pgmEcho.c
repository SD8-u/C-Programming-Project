/*Module to echo a logically equivalent pgm*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "exceptionHandling.h"

int main(int argc, char **argv){

	/*check correct number of arguments (3)*/	
	checkArgCount(argc, argc, 3, argv[0], 1);

	/*initialise pgm image*/
	pgmImage image = initPgmImage();

	/*read pgm data from specified file*/
	pgmRead(argv[1], &image, NULL, 0);

	/*write pgm to specified file*/
	pgmWrite(argv[2], &image, NULL, 0, 0);

	/*print "ECHOED" if no errors*/	
	printf("ECHOED\n");
	return 0; 
}
