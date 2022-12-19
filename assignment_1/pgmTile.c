/*Module to decompose given pgm into tiles, specified by integer factor*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "exceptionHandling.h"

/*copies part of a string with the given start/end integers*/
void copyString(char* template, int start, int end, 
char* string, int* count){
	
	for(int character = start; character < end; character++){
		int c = *count;
		string[c] = template[character];
		(*count)++;
	}
}

/*converts the row/column to a string and copies to the fileName*/
void copyPosition(int* count, char* fileName, int dimension, 
int digitLength, pgmImage *anImage, pgmImage *currentImage){

	/*allocate memory to digit for string representation*/
        char* digitString = malloc(digitLength * sizeof(char));
	checkMemoryAlloc(digitString, anImage, currentImage);
	
	/*convert dimension to a string*/        
	snprintf(digitString, digitLength + 1, "%d", dimension);
        
	/*copy number to fileName*/
	copyString(digitString, 0, digitLength, fileName, 
	count);
	
	free(digitString);
}

/*determine length of integer by repeated divison*/
int lengthOfInt(int num){
	int length = 1;
	while(num > 9){
		num/=10;
		length++;
	}
	return length;
}

/*process a given template by substituting the <row> and <column>
tags*/
char* processTemplate(char *template, int row, int column, int *brackets, 
pgmImage *anImage, pgmImage *cImage){

	/*initialise lengths of column and row dimensions*/
	int rowLength = lengthOfInt(row);
	int columnLength = lengthOfInt(column);
	int extLength = 0;	
	
	/*determine character length of file extension*/
	for(int chr = brackets[3]; template[chr] != '\0'; chr++){
		extLength++;
	}	

	/*allocate memory to fileName using length and bracket values*/
	char *fileName = (char *) malloc((brackets[0] + brackets[2] -
	brackets[1] + rowLength + columnLength + extLength) 
	* sizeof(char));
	checkMemoryAlloc(fileName, anImage, cImage);	

	/*generate fileName using length values and bracket positions*/
	int count = 0;

	/*start of template string before tag copied to fileName*/
	copyString(template, 0, brackets[0], fileName, &count);
	
	/*<row> is substituted for the current tile row*/
	copyPosition(&count, fileName, row, rowLength, 
	anImage, cImage);
	
	/*template string between tags is copied to fileName*/
	copyString(template, brackets[1] + 1, brackets[2], 
	fileName, &count);

	/*<column> is substituted for the current tile column*/
	copyPosition(&count, fileName, column, columnLength,
	anImage, cImage);
 
	/*file extension is added to fileName*/	
	copyString(template, brackets[3] + 1, brackets[3] +
	extLength, fileName, &count);

	fileName[count] = '\0';
        return fileName;
}

/*generates an individual tile/sub image of the original parent pgm*/
void createSubImage(char *fileName, pgmImage *anImage, int *brackets,
int width, int height, int regionRow, int regionColumn, int n){
                        
	/*initialise a tile pgm*/
        pgmImage image = initPgmImage();

        /*copy header data into pgm tile*/
        copyHeaderData(&image, anImage, width, height);

        /*allocate memory to pgm for insertion of image data*/
        allocateMemory(&image, anImage, NULL, 0, 1);

        /*iterate over current tile (region) in "parent" pgm and copy
        data to the tile pgm*/
        for(int row = regionRow; row < regionRow + height; row++){
        	for(int column = regionColumn; column < regionColumn
                + width; column++){

                	image.imageData[row-regionRow]
                        [column-regionColumn] =
                        anImage->imageData[row][column];
		}
	}

        /*Generate fileName*/
        char* imgName = processTemplate(fileName, regionRow/
        (anImage->height/n), regionColumn/(anImage->width/n),
        brackets, anImage, &image);

        /*write to generated fileName*/
        pgmWrite(imgName, &image, anImage, 1, 1);
}

/*writes all tiles of the original pgm file*/
void pgmTile(pgmImage *anImage, int n, char *fileName, int *brackets){

	/*calculate remainder of integer factor in height to distribute
 	over the tiles evenly (by adding to the incrementation in loop)*/

	int remainderHeight = anImage->height % n;

	/*iterates over each tile to produce the sub image*/
	for(int regionRow = 0; regionRow < anImage->height; regionRow+=
		(anImage->height/n + (remainderHeight >= 0))){
		
		/*calculate remainder of integer factor in width to distribute
                over the tiles evenly (by adding to the incrementation in loop)*/
	
		int remainderWidth = anImage->width % n;
		
		for(int regionColumn = 0; regionColumn < anImage->width; 
		regionColumn+=(anImage->width/n + (remainderWidth >= 0))){
			
			/*determine height and width of tile*/
			int height = anImage->height / n + 
			(remainderHeight > 0);
        		int width = anImage->width / n + 
			(remainderWidth > 0);
			
			createSubImage(fileName, anImage, brackets, 
			width, height, regionRow, regionColumn, n); 
			remainderWidth--;
		}
		remainderHeight--;
	}
}

int main(int argc, char **argv){
	
	/*check valid argument count*/
	checkArgCount(argc, argc, 4, argv[0], 4);
	
	/*check if template is valid*/
	int brackets[4]; 
	checkTemplate(argv[3], brackets);

        /*read integer factor and check validity*/
        checkIntegerFactor(argv[2]);
        int n = atoi(argv[2]);
	
	/*initialise pgmImage*/
	pgmImage anImage = initPgmImage();

	/*read in pgm image*/
	pgmRead(argv[1], &anImage, NULL, 0);

	/*call function to tile pgm into separate images*/
	pgmTile(&anImage, n, argv[3], 
	brackets);
	
	/*print "TILED" if no errors*/
	printf("TILED\n");

	/*cleanUp*/
	removePgmImage(&anImage);

	return 0;					

}
