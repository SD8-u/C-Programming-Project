//interfaces for Error functions
void checkArgCount(int noArg, int argc, int expectedArg, char *fileName, int errorMsg);

void checkOutputFileName(FILE *inputFile, char *fileName, pgmImage *anImage,
pgmImage *cImage, int multi, int dynamic);
void checkInputFileName(FILE *inputFile, char *fileName, pgmImage *cImage, int multi);

void checkOutput(FILE *outputFile, char *fileName,int nBytesWritten, pgmImage *anImage,
pgmImage *cImage, int multi);

void checkIntegerFactor(char* n);

void checkLayout(int argc);

void checkTemplate(char* template, int *brackets);

void checkMemoryAlloc(char* string, pgmImage *anImage, pgmImage *cImage);

void badFileName(char *fileName, int dynamic);

void badMagicNumber(char *fileName);

void badCommentLine(char *fileName);

void badDimensions(char *fileName);

void badMaxGreyValue(char *fileName);

void imageMallocFail();

void badData(char *fileName);

void outputFail(char *fileName);

void badIntegerFactor();

void badLayout();

void badTemplate();
