/*Module to check and handle errors strictly related to pgm files*/
/*include libraries*/
#include <stdio.h>
#include <stdlib.h>

/*include header files*/
#include "pgmImage.h"
#include "exceptionHandling.h"

/*pgm image structure constants*/
#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65535
#define MAX_COMMENT_LINE_LENGTH 128
#define MAX_GREY_VALUE 255

/*NOTE: cImage defines the current image being processed, allows for
memory to be freed of multiple pgmImage arrays at once*/

/*the multi paramater refers to whether there are multiple initialised pgm
structs*/

/*check validity of magic number*/
void checkMagicNumber(pgmImage *anImage, pgmImage *cImage, FILE *inputFile, 
char *fileName, int multi){
	/*verify magic number validity against correct values*/
        if(*anImage->magic_Number != MAGIC_NUMBER_ASCII_PGM && *anImage
	->magic_Number != MAGIC_NUMBER_RAW_PGM){
		/*system closure if invalid*/
		if(multi){
			removePgmImage(cImage);
		}
                fclose(inputFile);
                badMagicNumber(fileName);
        }
	/*determine file type and assign to pgm struct*/
	if(*anImage->magic_Number == MAGIC_NUMBER_RAW_PGM){
		anImage->binary = 1;	
	}
}

/*check memory allocation of each comment and comment length*/
void checkComment(int commentLength, char *fileName, FILE *inputFile,
pgmImage *cImage, int multi){
	/*close system if comment is too large*/
	if(commentLength > MAX_COMMENT_LINE_LENGTH){
		if(multi){
			removePgmImage(cImage);
		}
		fclose(inputFile);
		badCommentLine(fileName);	
	}
}

/*check dimensional values*/
void checkDimensions(FILE *inputFile, char *fileName, pgmImage *anImage, 
pgmImage *cImage, int multi){
	int width = anImage->width;
	int height = anImage->height;

	/*determine whether width/heigth in valid range*/	
	if((width == -1             ) || 
	(width < MIN_IMAGE_DIMENSION) ||
	(width > MAX_IMAGE_DIMENSION) ||
	(height ==-1		    ) ||
	(height < MIN_IMAGE_DIMENSION)||
	(height > MAX_IMAGE_DIMENSION)){
		/*close system/cleanUp if invalid*/
		if(multi){
			removePgmImage(cImage);
		}
		fclose(inputFile);
		badDimensions(fileName);	
	}
}

/*check maximum grey value*/
void checkMaxGreyValue(FILE *inputFile, char *fileName, int maxGrey,
pgmImage *cImage, int multi){
	/*determine whether maxGrey is within allowable values*/
	if((maxGrey == -1        ) ||
	(maxGrey > MAX_GREY_VALUE) ){
		if(multi){
			removePgmImage(cImage);
		}
		fclose(inputFile);
		badMaxGreyValue(fileName); 
	}
}

/*check memory allocation of each row*/ 
void checkImageData(int *data, FILE *inputFile,
pgmImage *anImage, pgmImage *cImage, int row,
int fileExists, int multi){
	/*determines whether allocation worked by
 	comaparing against NULL*/
	if(data == NULL){
		/*close file if open*/
		if(fileExists){
			fclose(inputFile);
		}
		/*free all allocated memory*/
		for(int data = 0; data <= row; data++){
                        free(anImage->imageData[data]);
                }
		free(anImage->imageData);
		if(multi){
			removePgmImage(cImage);
		}
		/*system closure*/
		imageMallocFail();
	}
}

/*check two dimensional memory allocation*/
void check2DImageData(int **data, FILE *inputFile,
pgmImage *anImage, pgmImage *cImage, int fileExists,
int multi){
	/*determines whether allocation worked by
        comaparing against NULL*/
	if(data == NULL){
		/*close file if open*/
		if(fileExists){
			fclose(inputFile);
		}
		if(multi){
			removePgmImage(cImage);
		}
		free(anImage->imageData);
		/*system closure*/
		imageMallocFail();
	}
}

/*check the validity of each colour value*/
void checkGreyValue(int greyValue, int count,
FILE *inputFile, char *fileName, pgmImage *anImage){
	/*determines whether a grey value is within allowed
 	values*/
	if((count != 1) || (greyValue < 0) || 
	(greyValue > MAX_GREY_VALUE)       ){
		/*system closure/cleanUp*/
		removePgmImage(anImage);
		fclose(inputFile);
		badData(fileName);
	}
}

/*check if end of file has been reached*/
void checkEOF(int binary, char *fileName, FILE *inputFile, 
pgmImage *anImage, pgmImage *cImage, int multi){
	/*if binary, use different reading function*/	
	if(binary){
		unsigned char value;
		fread(&value, 1, 1, inputFile);
	
		/*checks for unread values*/
		if(fread(&value, 1, 1, inputFile) > 0){
			/*system closure/cleanUp*/
			removePgmImage(anImage);
			if(multi){
				removePgmImage(cImage);
			}
                	fclose(inputFile);
                	badData(fileName);
		}
	}
	else {
		int value;
		/*checks for unread values*/
		if(fscanf(inputFile, " %d", &value) == 1){
			/*system closure/cleanUp*/
			removePgmImage(anImage);
			if(multi){
				removePgmImage(cImage);
			}
                	fclose(inputFile);
                	badData(fileName);	
		}
	}
}

/*checks whether pgm is of correct type for conversion*/
void checkFileType(pgmImage *anImage, char *fileName, int binary){
	/*checks magic number against given file type paramter*/
	if((binary && anImage->magic_number[1] != '5') ||
	 (!binary && anImage->magic_number[1] != '2')){
		removePgmImage(anImage);
		badMagicNumber(fileName);
	}
}
