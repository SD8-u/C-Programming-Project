all:	pgmEcho pgmComp	pgma2b	pgmb2a	pgmReduce pgmTile pgmAssemble
pgmEcho:	pgmEcho.c pgmImage.c pgmError.c exceptionHandling.c	pgmImage.h pgmError.h exceptionHandling.h
	gcc	-std=c99 	-o pgmEcho	pgmEcho.c pgmImage.c pgmError.c exceptionHandling.c pgmConversion.c
pgmComp:	pgmComp.c pgmImage.c pgmError.c exceptionHandling.c	pgmImage.h pgmError.h exceptionHandling.h
	gcc	-std=c99	-o pgmComp	pgmComp.c pgmImage.c pgmError.c exceptionHandling.c pgmConversion.c
pgma2b:		pgma2b.c pgmImage.c pgmError.c exceptionHandling.c pgmConversion.c	pgmImage.h pgmError.h exceptionHandling.h pgmConversion.h
	gcc	-std=c99	-o pgma2b	pgma2b.c pgmImage.c pgmError.c exceptionHandling.c pgmConversion.c
pgmb2a:		pgmb2a.c pgmImage.c pgmError.c exceptionHandling.c pgmConversion.c	pgmImage.h pgmError.h exceptionHandling.h pgmConversion.h
	gcc	-std=c99	-o pgmb2a	pgmb2a.c pgmImage.c pgmError.c exceptionHandling.c pgmConversion.c
pgmReduce:	pgmReduce.c pgmImage.c pgmError.c exceptionHandling.c	pgmImage.h pgmError.h exceptionHandling.h 
	gcc	-std=c99	-o pgmReduce	pgmReduce.c pgmImage.c pgmError.c exceptionHandling.c pgmConversion.c
pgmTile: 	pgmTile.c pgmImage.c pgmError.c exceptionHandling.c	pgmImage.h pgmError.h exceptionHandling.h
	gcc	-std=c99	-o pgmTile	pgmTile.c pgmImage.c pgmError.c exceptionHandling.c 
pgmAssemble:	pgmAssemble.c pgmImage.c pgmError.c exceptionHandling.c	pgmImage.h pgmError.h exceptionHandling.h
	gcc	-std=c99	-o pgmAssemble	pgmAssemble.c pgmImage.c pgmError.c exceptionHandling.c
clean:	
	rm *.o pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile pgmAssemble
