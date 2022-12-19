/*Module to facilitate conversion between ascii and binary pgm files*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "pgmError.h"
#include "exceptionHandling.h"

/*Converts given file to binary and writes to chosen output file*/
void pgmA2b(char *inputFileName, char *outputFileName){
	
	/*initialise pgm image*/
	pgmImage anImage = initPgmImage();
	
	/*read pgm data from file*/
	pgmRead(inputFileName, &anImage, NULL, 0);

	/*determine whether entered pgm is ascii*/
	checkFileType(&anImage, inputFileName, 0);
	
	/*convert header data to binary equivalent*/
	anImage.magic_number[0] = 'P';
	anImage.magic_number[1] = '5';
	anImage.binary = 1;

	/*write pgm to output file*/
	pgmWrite(outputFileName, &anImage, NULL, 0, 0);
	
}

/*converts given file to ascii and writes to chosen output file*/
void pgmB2a(char *inputFileName, char *outputFileName){
	
	/*initialise pgm image*/
	pgmImage anImage = initPgmImage();

	/*read pgm data from file*/
        pgmRead(inputFileName, &anImage, NULL, 0);
	
	/*determine whether entered pgm is binary*/
	checkFileType(&anImage, inputFileName, 1);

	/*convert header data to ascii equivalent*/
	anImage.magic_number[0] = 'P';
	anImage.magic_number[1] = '2';
	anImage.binary = 0;

	/*write pgm to output file*/
        pgmWrite(outputFileName, &anImage, NULL, 0, 0);
} 
