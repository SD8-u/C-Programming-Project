/*Module to decompose given gtopo into tiles, specified by integer factor*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
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
void copyPosition(int* count, char* fileName, int dimension, int digitLength, 
gtopoModel *dem, gtopoModel *cDem){

	/*allocate memory to digit for string representation*/
        char* digitString = malloc(digitLength * sizeof(char));
	checkMemoryAlloc(digitString, dem, cDem);
	int c = *count;        

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
gtopoModel *dem, gtopoModel *cDem){

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
        checkMemoryAlloc(fileName, dem, cDem);
        
        /*generate fileName using length values and bracket positions*/
        int count = 0;

        /*start of template string before tag copied to fileName*/
        copyString(template, 0, brackets[0], fileName, &count);

        /*<row> is substituted for the current tile row*/
        copyPosition(&count, fileName, row, rowLength,
        dem, cDem);

	/*template string between tags is copied to fileName*/
        copyString(template, brackets[1] + 1, brackets[2],
        fileName, &count);

	/*<column> is substituted for the current tile column*/
        copyPosition(&count, fileName, column, columnLength,
        dem, cDem);

        /*file extension is added to fileName*/
        copyString(template, brackets[3] + 1, brackets[3] +
        extLength, fileName, &count);

        fileName[count] = '\0';
        return fileName;
}
/*generates an individual tile/sub model of the original parent model*/
void createSubModel(char *fileName, gtopoModel *dem, int *brackets,
int width, int height, int regionRow, int regionColumn, int n){

	/*initialise a tile gtopo*/
        gtopoModel demTile = initGtopoModel(width, height, dem, 1);

        /*allocate memory to gtopo for insertion of data*/
        allocateMemory(&demTile, dem, NULL, 0, 1);

        /*iterate over current tile (region) in "parent" gtopo and copy
        data to the tile*/
        for(int row = regionRow; row < regionRow + height; row++){
        	for(int column = regionColumn; column < regionColumn
                + width; column++){

                	demTile.elevationData[row-regionRow]
                        [column-regionColumn] =
                        dem->elevationData[row][column];
                }
	}

        /*Generate fileName*/
        char* demName = processTemplate(fileName, regionRow/
        (dem->height/n), regionColumn/(dem->width/n),
        brackets, dem, &demTile);

        /*write to generated fileName*/
        gtopoWrite(demName, &demTile, dem, 1, 1);
}

/*writes all tiles of the original gtopo file*/
void gtopoTile(gtopoModel *dem, int n, char *fileName, 
int *brackets){

	/*calculate remainder of integer factor in height to distribute
        over the tiles evenly (by adding to the incrementation in loop)*/
	
	int remainderHeight = dem->height % n;

	/*iterates over each tile to produce the sub model*/
	for(int regionRow = 0; regionRow < dem->height; regionRow
		+=(dem->height/n +(remainderHeight >= 0))){

		/*calculate remainder of integer factor in width to distribute
                over the tiles evenly (by adding to the incrementation in loop)*/

		int remainderWidth = dem->width % n;

		for(int regionColumn = 0; regionColumn < dem->width; 
		regionColumn+=(dem->width/n + (remainderWidth >= 0))){
			
			/*determine height and width of tile*/
			int height = dem->height / n + 
			(remainderHeight > 0);
        		int width = dem->width / n + 
			(remainderWidth > 0);
			
			createSubModel(fileName, dem, brackets, 
			width, height, regionRow, regionColumn, n);
			remainderWidth--;
		}
		remainderHeight--;
	}
}

int main(int argc, char **argv){
	
	/*check valid argument count*/
	checkArgCount(argc, argc, 6, argv[0], 4);	

	/*check if template is valid*/
	int brackets[4];
        checkTemplate(argv[5], brackets);
	
	/*determine height and width*/
        checkInteger(argv[2], 0);
        int width = atoi(argv[2]);

        checkInteger(argv[3], 0);
        int height = atoi(argv[3]);
	
	/*read integer factor and check validity*/
        checkInteger(argv[4], 0);
        int n = atoi(argv[4]);

	/*initialise gtopo model*/
	gtopoModel dem = 
	initGtopoModel(width, height, NULL, 0);

	/*read in gtopo model*/
	gtopoRead(argv[1], &dem, NULL, 0);

	/*call function to tile pgm into separate images*/
	gtopoTile(&dem, n, argv[5], brackets);
	
	/*print "TILED" if no errors*/
	printf("TILED\n");

	/*cleanUp*/
	removeGtopoModel(&dem);

	return 0;					
}
