all:	gtopoEcho gtopoComp gtopoReduce gtopoTile gtopoAssemble gtopoPrintLand gtopoAssembleReduce
gtopoEcho:	gtopoEcho.c gtopoFormat.c gtopoError.c exceptionHandling.c gtopoFormat.h gtopoError.h exceptionHandling.h
	gcc	-g -std=c99 	-o gtopoEcho	gtopoEcho.c gtopoFormat.c gtopoError.c exceptionHandling.c 
gtopoComp:	gtopoComp.c gtopoFormat.c gtopoError.c exceptionHandling.c gtopoFormat.h gtopoError.h exceptionHandling.h
	gcc	-g -std=c99	-o gtopoComp	gtopoComp.c gtopoFormat.c gtopoError.c exceptionHandling.c
gtopoReduce:	gtopoReduce.c reduceUtilities.c gtopoFormat.c gtopoError.c exceptionHandling.c reduceUtilities.h gtopoFormat.h gtopoError.h exceptionHandling.h 
	gcc	-g -std=c99	-o gtopoReduce	gtopoReduce.c reduceUtilities.c gtopoFormat.c gtopoError.c exceptionHandling.c
gtopoTile: 	gtopoTile.c gtopoFormat.c gtopoError.c exceptionHandling.c gtopoFormat.h gtopoError.h exceptionHandling.h
	gcc	-g -std=c99	-o gtopoTile	gtopoTile.c gtopoFormat.c gtopoError.c exceptionHandling.c 
gtopoAssemble:	gtopoAssemble.c assembleUtilities.c gtopoFormat.c gtopoError.c exceptionHandling.c assembleUtilities.h gtopoFormat.h gtopoError.h exceptionHandling.h
	gcc	-g -std=c99	-o gtopoAssemble	gtopoAssemble.c assembleUtilities.c gtopoFormat.c gtopoError.c exceptionHandling.c
gtopoPrintLand: gtopoPrintLand.c gtopoFormat.c gtopoError.c exceptionHandling.c gtopoFormat.h gtopoError.h exceptionHandling.h
	gcc 	-g -std=c99	-o gtopoPrintLand	gtopoPrintLand.c gtopoFormat.c gtopoError.c exceptionHandling.c
gtopoAssembleReduce: gtopoAssembleReduce.c gtopoFormat.c gtopoError.c exceptionHandling.c assembleUtilities.c reduceUtilities.c gtopoFormat.h gtopoError.h exceptionHandling.h assembleUtilities.h reduceUtilities.h
	gcc	-g -std=c99	-o gtopoAssembleReduce	gtopoAssembleReduce.c gtopoFormat.c gtopoError.c exceptionHandling.c assembleUtilities.c reduceUtilities.c
clean:	
	rm *.o gtopoEcho gtopoComp gtopoReduce gtopoTile gtopoAssemble gtopoPrintLand gtopoAssembleReduce
