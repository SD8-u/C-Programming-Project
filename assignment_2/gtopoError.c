/*Module to check and handle errors strictly related to gtopo files*/
/*include libraries*/
#include <stdio.h>
#include <stdlib.h>

/*include header files*/
#include "gtopoFormat.h"
#include "exceptionHandling.h"

/*NOTE: cDem refers to current digital elevation model, it is required for
freeing all memory when processing multiple models, to avoid a memory leak*/

/*the multi paramater refers to whether there are multiple initialised gtopo
structs*/

/*check memory allocation of each row*/ 
void checkGtopoData(short *data, FILE *inputFile,
gtopoModel *dem, gtopoModel *cDem, int row, 
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
                        free(dem->elevationData[data]);
                }
		free(dem->elevationData);
		if(multi){
			removeGtopoModel(cDem);
		}
		/*system closure*/
		demMallocFail();
	}
}

/*check two dimensional memory allocation*/
void check2DGtopoData(short **data, FILE *inputFile,
gtopoModel *dem, gtopoModel *cDem, int fileExists, 
int multi){
	/*determines whether allocation worked by
        comaparing against NULL*/
	if(data == NULL){
		/*close file if open*/
		if(fileExists){
			fclose(inputFile);
		}
		if(multi){
			removeGtopoModel(cDem);
		}
		free(dem->elevationData);
		/*system closure*/
		demMallocFail();
	}
}

/*check if an elevation value was read*/
void checkElevationValue(int count, FILE *inputFile, char *fileName, 
gtopoModel *dem, gtopoModel *cDem, int multi){
	/*if the file ended or failed to read, close system*/
	if(feof(inputFile) || ferror(inputFile)){
		/*system closure/cleanUp*/
		removeGtopoModel(dem);
		if(multi){
			removeGtopoModel(cDem);
		}
		fclose(inputFile);
		badData(fileName);
	}
}

/*check if end of file has been reached*/
void checkEOF(char *fileName, FILE *inputFile, gtopoModel *dem,
gtopoModel *cDem, int multi){
	int value;
        fread(&value, 2, 1, inputFile);
        /*checks for unread values*/
	if(fread(&value, 2, 1, inputFile) > 0){
        	/*system closure/cleanUp*/
		removeGtopoModel(dem);
		if(multi){
			removeGtopoModel(cDem);
		}
        	fclose(inputFile);
        	badData(fileName);
	}
}
