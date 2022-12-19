/*Module to handle system closure and errors unrelated to pgm*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "exceptionHandling.h"

/*error codes*/
#define EXIT_NO_ARG_COUNT 0
#define EXIT_WRONG_ARG_COUNT 1
#define BAD_FILE_NAME 2 
#define DEM_MALLOC_FAIL 7
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
				printf("Usage: %s inputFile width height outputFile\n", fileName);
				break;
			case 2:
				printf("Usage: %s firstFile width height secondFile\n", fileName);
				break;
			case 3:
				printf("Usage: %s input width height reduction_factor output\n", fileName);
				break;
			case 4:
				printf("Usage: %s inputFile width height tiling_factor outputFile_<row>_<column>\n", fileName);
				break;
			case 5:
				printf("Usage: %s outputFile width height (row column inputFile width height)+\n",fileName);
				break;
			case 6:
				printf("Usage: %s inputFile width height outputFile sea hill mountain\n", fileName);
				break;
			case 7:
				printf("Usage: %s outputArray.gtopo width height (row column inputArray.gtopo)\n", fileName);
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

/*checks file name of specified file*/
void checkFileName(FILE *inputFile, char *fileName,
gtopoModel *dem, gtopoModel *cDem, int multi, int dynamic){
        if(inputFile == NULL){
                /*system closure on failed read*/
		removeGtopoModel(dem);
		if(multi){
			removeGtopoModel(cDem);
		}
                badFileName(fileName, dynamic);
        }
}

/*checks whether bytes written on output*/
void checkOutput(FILE *outputFile, char *fileName, 
int nBytesWritten, gtopoModel *dem, gtopoModel *cDem,
int multi){
	if(nBytesWritten < 0){
		removeGtopoModel(dem);
		fclose(outputFile);
		outputFail(fileName);
	}
}

/*checks whether integer factor is valid*/
void checkInteger(char* n, int negative){
	/*Each character must be between 0 and 9*/	
	int count = 0;
	while(*n){
		if(*n < '0' || *n > '9'){
			/*allow for sign if negative
			values are permitted*/
			if(negative){
				if(count || *n != '-'){
					badInteger();
				}
			}
			else{
				badInteger();
			}
		}
		count++;
		*n++;
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

/*checks validity of template for tile gtopo*/
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

/*check the allocation of memory*/
void checkMemoryAlloc(char* string, gtopoModel *dem,
gtopoModel *cDem){
	if(string == NULL){
		removeGtopoModel(dem);
		removeGtopoModel(cDem);
		demMallocFail();
	}
}

/*error messages and system closure*/
/*--------------------------------------------------------------*/
void badFileName(char *fileName, int dynamic){
	if(dynamic){
		free(fileName);
	}
	printf("ERROR: Bad File Name (%s)\n", fileName);
	exit(BAD_FILE_NAME);	
}

void demMallocFail(){
	printf("ERROR: Failed to allocate gtopo array memory\n");
	exit(DEM_MALLOC_FAIL);

}
void badData(char *fileName){
	printf("ERROR: Bad Data (%s)\n", fileName);
	exit(BAD_DATA);
}

void outputFail(char *fileName){
	printf("ERROR: Output Failed (%s)\n", fileName);
	exit(OUTPUT_FAIL);
}

void badInteger(){
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
/*--------------------------------------------------------------*/
