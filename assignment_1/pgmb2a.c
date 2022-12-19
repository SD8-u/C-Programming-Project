/*Module to convert binary pgm images to ascii*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmConversion.h"
#include "pgmImage.h"
#include "exceptionHandling.h"

int main(int argc, char **argv){
	
	/*check correct number of arguments (3)*/
	checkArgCount(argc, argc, 3, argv[0], 1);
        
	/*call to binary to ascii function*/
	pgmB2a(argv[1], argv[2]);
	
	/*print "CONVERTED" if no errors*/	
	printf("CONVERTED\n");

	return 0;
}
