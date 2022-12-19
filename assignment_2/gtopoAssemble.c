/*Module to create gtopo model from smaller gtopo files*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "assembleUtilities.h"
#include "exceptionHandling.h"

int main(int argc, char **argv){
			
	/*check user-entered integers*/
	for(int arg = 4; arg < argc; arg+=5){
		checkInteger(argv[arg], 0);
		checkInteger(argv[arg + 1], 0);
		checkInteger(argv[arg + 3], 0);
		checkInteger(argv[arg + 4], 0);
	}

	/*assemble full model from sub models*/	
	gtopoModel fullDem = 
	assembleFullModel(argc, argv, 0);
	
	/*write full model to output file*/
	gtopoWrite(argv[1], &fullDem, NULL, 0, 0);
	
	/*print "ASSEMBLED" if no errors*/
	printf("ASSEMBLED\n");
	
	return 0;
}
