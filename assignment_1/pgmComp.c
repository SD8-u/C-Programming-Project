/*Module to logically compare pgm images*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "pgmImage.h"
#include "exceptionHandling.h"
#include "pgmError.h"

/*compares the logical equivalence of two given pgm images*/
int comparePgm(pgmImage img1, pgmImage img2){

	/*check whether the resolution is equal*/
	if((img1.width == img2.width) && (img1.height == img2.height)){

		/*check whether each grey value of each image is logically
  		equivalent*/
		for(int row = 0; row < img1.height; row++){
			for(int column = 0; column < img1.width; column++){
				
				/*if not equal, return false (0)*/
				if((double)img1.imageData[row][column]/
				img1.maxGrey != (double)
				img2.imageData[row][column]/img2.maxGrey){
					return 0;
				}	
			}		
		}		
	}
	else{
		return 0;
	}
	/*return true if no values were logically different*/
	return 1;
}


int main(int argc, char **argv){
	
	/*check correct number of arguments*/
	checkArgCount(argc, argc, 3, argv[0], 2);

	/*initialise two pgm images*/
	pgmImage img1 = initPgmImage();

	pgmImage img2 = initPgmImage();

	/*read data of each pgm image from
 	specified file*/
	pgmRead(argv[1], &img1, NULL, 0);

	pgmRead(argv[2], &img2, &img1, 1);

	/*determine whether they are logically
	equivalent*/	
	int equal = comparePgm(img1, img2);
	
	if(equal){
		printf("IDENTICAL\n");
	}
	else{
		printf("DIFFERENT\n");
	}

	/*cleanUp*/
	removePgmImage(&img1);
	removePgmImage(&img2);
	return 0;
}
