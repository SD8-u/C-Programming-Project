/*Module to provide utilities for assembling gtopo*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "gtopoError.h"
#include "exceptionHandling.h"

/*copies sub model data to full model*/
void spliceSubModels(char** argv, gtopoModel *fullDem, int argc, int reduce){

        /*iterate through each of the sub models in the command line
        arguments*/
        for(int arg = 4 + reduce; arg < argc; arg+=5){

                /*initialise sub model and assign starting values*/
                gtopoModel subDem;
                subDem = initGtopoModel(atoi(argv[arg + 3]),
                atoi(argv[arg + 4]), fullDem, 1);

                int startRow = atoi(argv[arg]);
                int startColumn = atoi(argv[arg + 1]);

                /*read in subImage*/
                gtopoRead(argv[arg + 2], &subDem, fullDem, 1);

                /*iterate through each subimage, assigning its value
                to the correct position in the full image*/
                for(int row = startRow; row < subDem.height + startRow;
                row++){
                        for(int column = startColumn; column < subDem.width +
                        startColumn; column++){

                                fullDem->elevationData[row][column] =
                                subDem.elevationData[row-startRow]
                                [column-startColumn];
                        }
                }

                /*cleanUp subImage*/
                removeGtopoModel(&subDem);
        }

}

/*assembles full gtopo from sub models*/
gtopoModel assembleFullModel(int argc, char **argv, int reduce){

        /*uses arg count to determine correct number
        of arguments have been entered*/
	checkArgCount(argc, 
	((argc - (4 + reduce)) % 5), 0, argv[0], 5 + reduce * 2);

        /*determine width and height*/
        checkInteger(argv[2], 0);
        int width = atoi(argv[2]);

        checkInteger(argv[3], 0);
        int height = atoi(argv[3]);	

        /*full gtopo model initialised*/
        gtopoModel fullDem =
        initGtopoModel(width, height, NULL, 0);

        /*allocate memory for model data*/
        allocateMemory(&fullDem, NULL, NULL, 0, 0);

        /*assemble full gtopo from sub models*/
        spliceSubModels(argv, &fullDem, argc, reduce);

        return fullDem;
}
