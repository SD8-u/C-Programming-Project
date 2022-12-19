//interfaces for Error functions
void checkArgCount(int noArg, int argc, int expectedArg, char *fileName, int errorMsg);

void checkFileName(FILE *inputFile, char *fileName, gtopoModel *dem,
gtopoModel *cDem, int multi, int dynamic);

void checkOutput(FILE *outputFile, char *fileName,int nBytesWritten, gtopoModel *dem,
gtopoModel *cDem, int multi);

void checkInteger(char* n, int negative);

void checkLayout(int argc);

void checkTemplate(char* template, int *templateStart);

void checkMemoryAlloc(char* string, gtopoModel *dem, gtopoModel *cDem);

void badFileName(char *fileName, int dynamic);

void badMagicNumber(char *fileName);

void badCommentLine(char *fileName);

void badDimensions(char *fileName);

void badMaxGreyValue(char *fileName);

void demMallocFail();

void badData(char *fileName);

void outputFail(char *fileName);

void badInteger();

void badLayout();

void badTemplate();
