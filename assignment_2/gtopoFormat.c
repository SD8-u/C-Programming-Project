/*Module to control initilisation, read, write, and removal of gtopoModels*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "exceptionHandling.h"
#include "gtopoError.h"

/*initialises data for a gtopo structure*/
gtopoModel initGtopoModel(int width, int height, gtopoModel *cDem,
int multi){

	/*define gtopo structure*/
	gtopoModel dem;

	/*initialise fields*/
	dem.width = width;
	dem.height = height;

	/*allocate data array memory*/
	allocateMemory(&dem, cDem, NULL, 0, multi); 	

	return dem;
}

/*Removes a pgm image structure*/
void removeGtopoModel(gtopoModel *dem){

	/*free memory associated with pgm image data*/
	for(int row = 0; row < dem->height; row++){
		free(dem->elevationData[row]);
	}
	
	free(dem->elevationData);
}

/*reverse bytes in number for endian conversion*/
short convertEndian(short n){
	/*swap bytes by shifting 8 bits on either side
	bitmask used to remove sign bit on right shift*/
	return (n << 8) | ((n >> 8) & 0xFF);	
}

/*allocates memory for the image data of a pgm structure*/
void allocateMemory(gtopoModel *dem, gtopoModel *cDem, FILE *inputFile, 
int fileExists, int multi){
	
        /*allocate memory for arrays*/
        dem->elevationData = (short **) malloc(dem->height * sizeof(short *));

        /*check allocation of memory for pointer array of image data*/
        check2DGtopoData(dem->elevationData, inputFile,
        dem, cDem, fileExists, multi);

        for(int row = 0; row < dem->height; row++){
                dem->elevationData[row] = (short *) malloc(dem->width *
                sizeof(short));

                /*check memory allocation for each row*/
                checkGtopoData(dem->elevationData[row], inputFile,
                dem, cDem, row, fileExists, multi);
        }
}

/*reads and stores elevation values of gtopo in 2D array*/
void gtopoRead(char *fileName, gtopoModel *dem, gtopoModel *cDem,
int multi) {
	
	FILE *inputFile = fopen(fileName, "r");
        checkFileName(inputFile, fileName, dem, cDem, multi, 0);
	
	/*read in each elevation value of the gtopo*/
	for(int row = 0; row < dem->height; row++){
		for(int column = 0; column < dem->width; column++){
	
			short elevationValue;

                        /*gtopoError check elevation value was read*/
                        checkElevationValue(fread(&elevationValue, 2, 
			1, inputFile), inputFile, fileName, dem, 
			cDem, multi);
		
			elevationValue = 
			convertEndian(elevationValue);
			
			dem->elevationData[row][column] = 
			elevationValue;
		}
	}
	/*ensure end of file has been reached*/
	checkEOF(fileName, inputFile, dem, cDem, multi);
	fclose(inputFile);
}

/*writes a gtopo file from its data structure in memory*/
void gtopoWrite(char *fileName, gtopoModel *dem, gtopoModel *cDem,
int multi, int dynamic){
	
	FILE *outputFile = fopen(fileName, "w");

	/*check file opened*/
	checkFileName(outputFile, fileName, dem, cDem, multi, 
	dynamic);
	
	/*if filename has been allocated memory (i.e. dynamic)*/
	if(dynamic){
		free(fileName);
	}

	int nBytesWritten = -1;
	/*write elevation data*/	
        for(int row = 0; row < dem->height; row++){
                for(int column = 0; column < dem->width; column++){
			
			short elevationValue = convertEndian(dem->
			elevationData[row][column]);

			nBytesWritten = fwrite(&elevationValue, 2, 1, 
			outputFile);
			
			/*check bytes written*/
			checkOutput(outputFile, fileName, 
			nBytesWritten, dem, cDem, multi);
                }
        }
	/*cleanUp*/
	removeGtopoModel(dem);
        fclose(outputFile);
}            
