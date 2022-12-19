/*Module to reduce pgm image by specified integer factor*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "pgmError.h"
#include "exceptionHandling.h"

/*returns a new pgm, a reduction of the given pgm by the specified 
integer factor*/
pgmImage reducePgm(pgmImage *anImage, int n, char *fileName){
	
	/*initialise reduced pgm*/
	pgmImage reducedPgm = initPgmImage();

	/*determine width/height of reduced pgm*/
	int width = anImage->width / n + (anImage->width % n > 0);
	int height = anImage->height / n + (anImage->height %n > 0);

	/*copy header data to reduced pgm*/
	copyHeaderData(&reducedPgm, anImage, width, height);

	/*allocate memory for image data arrays*/
	allocateMemory(&reducedPgm, anImage, NULL, 0, 1);

	/*iterate over values for the reduced image*/
	for(int row = 0; row < anImage->height; row+=n){
		for(int column = 0; column < anImage->width; column+=n){
			
			/*assign corresponding 
 			grey values to the reduced pgm's data*/
			reducedPgm.imageData[row/n][column/n] 
			= anImage->imageData[row][column];		
		}
	}

	return reducedPgm;	
}

int main(int argc, char **argv){
	
	/*check correct number of arguments (4)*/
	checkArgCount(argc, argc, 4, argv[0], 3);

	/*convert specified integer factor to an integer*/
        checkIntegerFactor(argv[2]);
        int n = atoi(argv[2]);

	/*initialise pgm image*/
	pgmImage image = initPgmImage();

	/*read pgm image using specified file*/
	pgmRead(argv[1], &image, NULL, 0);	

	/*create reduced image by calling to reduce function*/
	pgmImage reducedImage = reducePgm(&image, n, 
	argv[1]);

	/*write pgm to file*/
	pgmWrite(argv[3], &reducedImage, &image, 1, 0);

	/*print "REDUCED" if no errors occured*/	
	printf("REDUCED\n");

	/*cleanUp*/
	removePgmImage(&image);
	return 0; 	
}
