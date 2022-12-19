/*Module to assemble and reduce given gtopo tiles*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "gtopoError.h"
#include "exceptionHandling.h"
#include "assembleUtilities.h"
#include "reduceUtilities.h"

int main(int argc, char **argv){

	/*check user-entered integers*/
	checkInteger(argv[4], 0);
	for(int arg = 5; arg < argc; arg+=5){    
                checkInteger(argv[arg], 0);
		checkInteger(argv[arg + 1], 0);
		checkInteger(argv[arg + 3], 0);
		checkInteger(argv[arg + 4], 0);
        }

	/*use gtopo assemble to firstly 
	assemble full model*/
	gtopoModel fullDem = 
	assembleFullModel(argc, argv, 1);

	/*use gtopo reduce to compress 
	assembled model*/
	gtopoModel reducedDem = 
	reduceGtopo(&fullDem, atoi(argv[4]));

	/*cleanUp fullDem from memory*/
	removeGtopoModel(&fullDem);

	/*write reducedDem to disk*/
	gtopoWrite(argv[1], &reducedDem, NULL, 0, 0);

	/*print "ASSEMBLED REDUCED" if no errors*/
	printf("ASSEMBLED REDUCED\n");

	return 0;
}
