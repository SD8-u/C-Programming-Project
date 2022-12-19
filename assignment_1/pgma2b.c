/*Module to convert ascii pgm images to binary*/
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
        
	/*call to ascii to binary function*/
	pgmA2b(argv[1], argv[2]);
	
	/*print "CONVERTED" if no errors*/	
	printf("CONVERTED\n");

	return 0;

}
