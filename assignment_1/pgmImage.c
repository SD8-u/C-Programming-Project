/*Module to control initilisation, read, write, and removal of pgmImages*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "exceptionHandling.h"
#include "pgmError.h"

/*initialises data for a pgm structure*/
pgmImage initPgmImage(){

	/*define pgm structure*/
	pgmImage anImage;

	/*initialise fields*/
	anImage.magic_number[0] = '0';
	anImage.magic_number[1] = '0';
	anImage.magic_Number = (unsigned short *) anImage.
	magic_number;
	anImage.width = -1;
	anImage.height = -1;
	anImage.maxGrey = -1;
	anImage.binary = 0;
	
	return anImage;
}

/*Removes a pgm image structure*/
void removePgmImage(pgmImage *anImage){

	/*free memory associated with pgm image data*/
	for(int row = 0; row < anImage->height; row++){
		free(anImage->imageData[row]);
	}

	free(anImage->imageData);
}

/*checks for comments and their validity*/
void readComments(FILE *inputFile, char *fileName,
pgmImage *cImage, int multi){

	int whiteSpace = fscanf(inputFile, " ");
        char next = fgetc(inputFile);

        /*check for comments*/
        if(next == '#') {
        	/*iterate over all comments in pgm*/
        	while(next == '#'){

			/*count length of comment*/
			int commentLength = 0;
			char commentChr = fgetc(inputFile);
			while(commentChr != '\n'){
				
				commentChr = fgetc(inputFile);
				commentLength++;	
			}
       
                	/*call to pgmError to check comment*/
                	checkComment(commentLength, fileName, 
			inputFile, cImage, multi);

			next = fgetc(inputFile);
        	}
	}
	ungetc(next, inputFile);	
}

/*reads and checks magic number*/
void readMagicNumber(pgmImage *anImage, pgmImage *cImage, FILE *inputFile, 
char *fileName, int multi){
	
	/*check for comments*/
        readComments(inputFile, fileName, cImage, multi);

        /*read magic number*/
        anImage->magic_number[0] = getc(inputFile);
        anImage->magic_number[1] = getc(inputFile);
        anImage->magic_Number = (unsigned short *) anImage->
        magic_number;

        /*check magic number*/
        checkMagicNumber(anImage, cImage, inputFile,
        fileName, multi);
}

/*copies the image properties of a "parent" pgm*/
void copyHeaderData(pgmImage *image, pgmImage *anImage,
int width, int height){

        image->binary = anImage->binary;
        image->magic_number[0] = anImage->magic_number[0];
        image->magic_number[1] = anImage->magic_number[1];
        image->height = height;
        image->width = width;
        image->maxGrey = anImage->maxGrey;
}

/*reads header data, avoiding any comments and checking data validity*/
void processHeader(FILE *inputFile, char *fileName, pgmImage *anImage,
pgmImage *cImage, int multi){

	/*read magic number*/
	readMagicNumber(anImage, cImage, inputFile, fileName, multi);
	
        /*check for comments*/
        readComments(inputFile, fileName, cImage, multi);

        /*read in dimensions and maxGrey value*/
        /*comments are checked for between each value*/
        int readCount = fscanf(inputFile, " %d ", &(anImage->width));

        readComments(inputFile, fileName, cImage, multi);

        readCount = fscanf(inputFile, " %d ", &(anImage->height));
        checkDimensions(inputFile, fileName, anImage, cImage, multi);

        readComments(inputFile, fileName, cImage, multi);

        readCount = fscanf(inputFile, " %d ", &(anImage->maxGrey));
        checkMaxGreyValue(inputFile, fileName, anImage->maxGrey,
	cImage, multi);

        readComments(inputFile, fileName, cImage, multi);
	
        /*allocate memory using read height and width values*/
        allocateMemory(anImage, cImage, inputFile, 1, multi);
}

/*allocates memory for the image data of a pgm structure*/
void allocateMemory(pgmImage *anImage, pgmImage *cImage, FILE *inputFile, 
int fileExists, int multi){
	
        /*allocate memory for arrays*/
        anImage->imageData = (int **) malloc(anImage->height * sizeof(int *));

        /*check allocation of memory for pointer array of image data*/
        check2DImageData(anImage->imageData, inputFile,
        anImage, cImage, fileExists, multi);

        for(int row = 0; row < anImage->height; row++){
                anImage->imageData[row] = (int *) malloc(anImage->width *
                sizeof(int));

                /*check memory allocation for each row*/
                checkImageData(anImage->imageData[row], inputFile,
                anImage, cImage, row, fileExists, multi);
        }
}

/*reads a singluar grey value into a pgm image struct*/
void readGreyValue(char *fileName, pgmImage *anImage, pgmImage *cImage, 
int multi, int row, int column, FILE *inputFile){

	int greyCount;
	int greyValue = -1;
        /*read using fread if pgm is binary*/
        if(anImage->binary){
        	unsigned char value;
                greyCount = fread(&value, 1, 1, inputFile);
                greyValue = (int)value;
        }
        else{
                greyCount = fscanf(inputFile, " %d", &greyValue);
        }
        /*pgmError check grey value*/
        checkGreyValue(greyValue, greyCount,
        inputFile, fileName, anImage, cImage, multi);

        anImage->imageData[row][column] = greyValue;

}

/*reads and stores colour values of pgm in 2D array*/
void pgmRead(char *fileName, pgmImage *anImage, pgmImage *cImage,
int multi) {	

	FILE *inputFile = fopen(fileName, "r");

	/*check if file opened*/
        checkInputFileName(inputFile, fileName, cImage, multi);

	/*read all comments and header values*/
	processHeader(inputFile, fileName, anImage, cImage, multi);
	
	/*read in each colour value of the pgm*/
	for(int row = 0; row < anImage->height; row++){
		for(int column = 0; column < anImage->width; column++){

			readGreyValue(fileName, anImage, cImage, multi,
			row, column, inputFile);
		}
	}
	/*ensure end of file has been reached*/
	checkEOF(anImage->binary, fileName, inputFile, anImage, 
	cImage, multi);
	fclose(inputFile);
}

/*writes a singular grey value from pgm image stuct*/
void writeGreyValue(char *fileName, pgmImage *anImage, pgmImage *cImage, 
int multi, int row, int column, FILE *outputFile){
	
	size_t nBytesWritten;
	/*written using fwrite if binary*/
	if(anImage->binary){
	
		int greyValue = anImage->
                imageData[row][column];

                nBytesWritten = fwrite(&greyValue, 1, 1,
                outputFile);
	}
        else{
                nBytesWritten = fprintf(outputFile, "%d",
		anImage->imageData[row][column]);

		/*write a space between each value*/	
		if(column != anImage->width - 1){
			fprintf(outputFile, " ");
		}
        }

        /*check bytes written*/
        checkOutput(outputFile, fileName, nBytesWritten,
        anImage, cImage, multi);
}

/*writes a logically equivalent pgm image*/
void pgmWrite(char *fileName, pgmImage *anImage, pgmImage *cImage,
int multi, int dynamic){
	
	FILE *outputFile = fopen(fileName, "w");
	size_t nBytesWritten;        

	/*check file opened*/
	checkOutputFileName(outputFile, fileName, anImage, cImage, multi,
	dynamic);
	
	/*if filename has been allocated memory (i.e. dynamic)*/
        if(dynamic){
                free(fileName);
        }

	/*write ONLY header data*/
        nBytesWritten = fprintf(outputFile, "%c%c\n%d %d\n%d\n", anImage->
	magic_number[0], anImage->magic_number[1], anImage->width, 
	anImage->height, anImage->maxGrey);

	/*check output of header data*/
	checkOutput(outputFile, fileName, nBytesWritten, anImage, 
	cImage, multi);
	
	/*write image data*/	
        for(int row = 0; row < anImage->height; row++){
                for(int column = 0; column < anImage->width; column++){
			
			writeGreyValue(fileName, anImage, cImage, multi,
			row, column, outputFile); 		
                }
		if(!anImage->binary){
			fprintf(outputFile, "\n");
		}
        }
	
	/*cleanUp*/
	removePgmImage(anImage);
        fclose(outputFile);
}            
