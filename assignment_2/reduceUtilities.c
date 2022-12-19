/*Module to provide utilities for gtopo reduce*/
/*libraries*/
#include <stdio.h>
#include <stdlib.h>

/*implemented modules*/
#include "gtopoFormat.h"
#include "gtopoError.h"
#include "exceptionHandling.h"

/*returns a new pgm, a reduction of the given pgm by the specified
integer factor*/
gtopoModel reduceGtopo(gtopoModel *dem, int n){

	/*determine width/height of reduced gtopo*/
	int width = dem->width / n + (dem->width % n > 0);
	int height = dem->height / n + (dem->height % n > 0);
        
	/*initialise reduced gtopo*/
        gtopoModel reducedDem = initGtopoModel(width,
        height, dem, 1);

        /*allocate memory for image data arrays*/
        allocateMemory(&reducedDem, dem, NULL, 0, 1);

        /*iterate over values for the reduced image*/
        for(int row = 0; row < dem->height; row+=n){
                for(int column = 0; column < dem->width; column+=n){

                        /*assign corresponding
                        grey values to the reduced pgm's data*/
                        reducedDem.elevationData[row/n][column/n]
                        = dem->elevationData[row][column];
                }
        }

        return reducedDem;
}
