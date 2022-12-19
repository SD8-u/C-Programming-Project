/*Module to create pgm image from smaller images*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "pgmError.h"
#include "exceptionHandling.h"	

/*assembles sub images into one full image*/
void spliceSubImages(char** argv, pgmImage *fullImage, int argc){
        
	/*iterate through each of the subImages in the command line
 	arguments*/
	for(int arg = 4; arg < argc; arg+=3){

		/*initialise subImage and assign starting values*/
		pgmImage subImage = initPgmImage();
                int startRow = atoi(argv[arg]);
                int startColumn = atoi(argv[arg + 1]);

		/*read in subImage*/
                pgmRead(argv[arg + 2], &subImage, fullImage, 1);

		/*iterate through each subimage, assigning its value
		to the correct position in the full image*/
                for(int row = startRow; row < subImage.height + startRow; 
		row++){
                        for(int column = startColumn; column < subImage.width +
                        startColumn; column++){
	
                                fullImage->imageData[row][column] = 
				subImage.imageData[row-startRow]
				[column-startColumn];
                        }
                }
		
		/*copy subImage header data into the full image*/
                copyHeaderData(fullImage, &subImage, fullImage->width,
		fullImage->height);	

		/*cleanUp subImage*/
                removePgmImage(&subImage);
        }

}

int main(int argc, char **argv){
	
	/*uses argCount to determine if any arguments have
	been entered*/
	checkArgCount(argc, (argc - 1) % 3, 0, argv[0], 5);

	/*check all user-entered integer values*/
	checkIntegerFactor(argv[2]);
        checkIntegerFactor(argv[3]);

	for(int arg = 4; arg < argc; arg+=3){
		checkIntegerFactor(argv[arg]);
		checkIntegerFactor(argv[arg + 1]);
	}

	/*full image pgm initialised*/
	pgmImage fullImage = initPgmImage();
	
	fullImage.width = atoi(argv[2]);
        fullImage.height = atoi(argv[3]);
	
	/*allocate memory to imagedata*/
	allocateMemory(&fullImage, NULL, NULL, 0, 0); 
	
	/*assemble full image from subImages*/
	spliceSubImages(argv, &fullImage, argc);
	
	/*write image to output file*/
	pgmWrite(argv[1], &fullImage, NULL, 0, 0);
	
	/*print "ASSEMBLED" if no errors*/
	printf("ASSEMBLED\n");

	return 0;
}
