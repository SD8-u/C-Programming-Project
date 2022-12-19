/*Module to handle system closure and errors unrelated to pgm*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "exceptionHandling.h"

/*error codes*/
#define EXIT_NO_ARG_COUNT 0
#define EXIT_WRONG_ARG_COUNT 1
#define BAD_FILE_NAME 2 
#define BAD_MAGIC_NUMBER 3
#define BAD_COMMENT_LINE 4
#define BAD_DIMENSIONS 5
#define BAD_MAX_GREY_VALUE 6
#define IMAGE_MALLOC_FAIL 7
#define BAD_DATA 8
#define OUTPUT_FAIL 9
#define BAD_LAYOUT 10
#define MISCELLANEOUS 100

/*check arguments against expected argument count*/
void checkArgCount(int noArg, int argc, int expectedArg, char *fileName,
int errorMsg){
	if(noArg == 1){
		/*error message and system closure on no arguments*/
		/*integer encodes error message via switch statement*/
		switch(errorMsg){
			case 1:
				printf("Usage: %s inputImage.pgm outputImage.pgm\n", fileName);
				break;
			case 2:
				printf("Usage: %s inputImage.pgm inputImage.pgm\n", fileName);
				break;
			case 3:
				printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", fileName);
				break;
			case 4:
				printf("Usage: %s inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm\n", fileName);
				break;
			case 5:
				printf("Usage: %s outputImage.pgm width height (row column inputImage.pgm)+\n",fileName);
				break;
				
		}
		exit(EXIT_NO_ARG_COUNT); 
	}
	/*invalid number of arguments*/
	else if(argc != expectedArg){
		printf("ERROR: Bad Argument Count\n");
		exit(EXIT_WRONG_ARG_COUNT);
	}
}

/*checks file name of specified output file*/
void checkOutputFileName(FILE *inputFile, char *fileName, 
pgmImage *anImage, pgmImage *cImage, int multi, int dynamic){
	if(inputFile == NULL){
		/*system closure on failed read*/
		if(multi){
			removePgmImage(cImage);
		}
		removePgmImage(anImage);
		badFileName(fileName, dynamic);
	}
}

/*checks file name of specified input file*/
void checkInputFileName(FILE *inputFile, char *fileName, 
pgmImage *cImage, int multi){
        if(inputFile == NULL){
                /*system closure on failed read*/
		if(multi){
			removePgmImage(cImage);
		}
                badFileName(fileName, 0);
        }
}

/*checks whether bytes written on output*/
void checkOutput(FILE *outputFile, char *fileName, 
int nBytesWritten, pgmImage *anImage, pgmImage 
*cImage, int multi){
	if(nBytesWritten < 0){
		if(multi){
			removePgmImage(cImage);
		}
		removePgmImage(anImage);
		fclose(outputFile);
		outputFail(fileName);
	}
}

/*checks whether integer factor is valid*/
void checkIntegerFactor(char* n){
	int count = 0;	
	while(*n){
		/*each character must be 
  		between 0 and 9*/
		if(*n < '0' || *n > '9'){
			badIntegerFactor();
		}
		*n++;
	}
}

/*checks whether an assembly layout is valid*/
void checkLayout(int argc){
	if((argc - 1) % 3 > 0){
		badLayout();
	}
}

/*determines whether a tag is valid*/
int validTag(char *template, int *brackets, int position, 
int *character){
	int rowFirst = 0;
	char *rowTag = "row>";
	char *columnTag = "column>";
	
	/*check if tag is for row or column*/
        if(template[++(*character)] == 'r'){
        	if(rowFirst){
                	return 0;
        	}
        	rowFirst = 1;
        }
	
	/*iterate through tag to determine validity*/
        for(int x = brackets[position] + 1;
        	template[x] != '>'; x++){
                /*compare each tag character to valid
		tag characters*/
                if((rowFirst && template[x] !=
                rowTag[x-brackets[position]    - 1]) ||
              	(  !rowFirst && template[x] !=
                columnTag[x-brackets[position] - 1]) ){
                	return 0;
                }
	    	(*character)++;
        }
	/*check entire tag is present in template*/
        if(((rowFirst && (*character)-brackets[position] < 4) ||
        (!rowFirst && (*character)-brackets[position] < 7))   ){
        	return 0;
        }
}

/*checks validity of template for tile pgm*/
void checkTemplate(char* template, int *brackets){
	
	int valid = 1;
	int position = -1;
	int tagNum = 0;
	/*iterates through template, checking its validity*/
 	for(int character = 0; template[character] != '\0'; character++){

		/*determines the start of the dimensional tags*/
		if(template[character] == '<'){
		
			brackets[++position] = character;
			tagNum++;
			/*check each tags validity*/
			if(!validTag(template, brackets, position, 
			&character)){
				valid = 0;
				break;
			}
			brackets[++position] = character;
		}
	}
	/*exit if template is invalid*/
	if(!valid || tagNum != 2){
		badTemplate();
	}
}

/*check allocation of memory to string*/
void checkMemoryAlloc(char* string, pgmImage *anImage,
pgmImage *cImage){
	if(string == NULL){
		removePgmImage(anImage);
		removePgmImage(cImage);
		imageMallocFail();
	}
}

/*error messages and system closure*/
/*---------------------------------------------------------------*/
void badFileName(char *fileName, int dynamic){
	printf("ERROR: Bad File Name (%s)\n", fileName);
	if(dynamic){
		free(fileName);
	}
	exit(BAD_FILE_NAME);	
}

void badMagicNumber(char *fileName){
	printf("ERROR: Bad Magic Number (%s)\n", fileName);
	exit(BAD_MAGIC_NUMBER);
}

void badCommentLine(char *fileName){
	printf("ERROR: Bad Comment Line (%s)\n", fileName);
	exit(BAD_COMMENT_LINE);
}

void badDimensions(char *fileName){
	printf("ERROR: Bad Dimensions (%s)\n", fileName);
	exit(BAD_DIMENSIONS);	
}

void badMaxGreyValue(char *fileName){
	printf("ERROR: Bad Max Gray Value (%s)\n", fileName);
	exit(BAD_MAX_GREY_VALUE);
}

void imageMallocFail(){
	printf("ERROR: Image Malloc Failed\n");
	exit(IMAGE_MALLOC_FAIL);

}
void badData(char *fileName){
	printf("ERROR: Bad Data (%s)\n", fileName);
	exit(BAD_DATA);
}

void outputFail(char *fileName){
	printf("ERROR: Output Failed (%s)\n", fileName);
	exit(OUTPUT_FAIL);
}

void badIntegerFactor(){
	printf("ERROR: Miscellaneous (Bad integer)\n");
	exit(MISCELLANEOUS);
}

void badLayout(){
	printf("ERROR: Bad Layout\n");
	exit(BAD_LAYOUT);
}

void badTemplate(){
	printf("ERROR: Miscellaneous (Bad Template)\n");
        exit(MISCELLANEOUS);
}
/*---------------------------------------------------------------*/
