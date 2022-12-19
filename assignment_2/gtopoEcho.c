/*Module to echo an equivalent gtopo file*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "exceptionHandling.h"

int main(int argc, char **argv){

	/*check correct number of arguments (3)*/	
	checkArgCount(argc, argc, 5, argv[0], 1);

	/*check width and height (integer)*/
	checkInteger(argv[2], 0);
	checkInteger(argv[3], 0);

	/*initialise width/height*/
	int width = atoi(argv[2]);
	int height = atoi(argv[3]);

	/*initialise gtopo structure*/
	gtopoModel dem = 
	initGtopoModel(width, height, NULL, 0);

	/*read gtopo data from specified file*/
	gtopoRead(argv[1], &dem, NULL, 0);

	/*write gtopo to specified file*/
	gtopoWrite(argv[4], &dem, NULL, 0, 0);

	/*print "ECHOED" if no errors*/
	
	printf("ECHOED\n");
	return 0; 
}
