//interfaces for functions in pgmError
void checkMagicNumber(pgmImage *anImage, pgmImage *cImage, FILE *inputFile, char *fileName,
int multi);

void checkComment(int commentLength, char *fileName, FILE *inputFile, pgmImage *cImage, 
int multi);

void checkDimensions(FILE *inputFile, char *fileName, pgmImage *anImage, pgmImage *cImage,
int multi);
void checkMaxGreyValue(FILE *inputFile, char *fileName, int dimension, pgmImage *cImage, 
int multi);

void checkImageData(int *data, FILE *inputFile, pgmImage *anImage, pgmImage *cImage, int row, 
int fileExists, int multi);
void check2DImageData(int **data, FILE *inputFile, pgmImage *anImage, pgmImage *cImage, 
int fileExists, int multi);

void checkGreyValue(int greyValue, int count, FILE *inputFile, char *fileName, 
pgmImage *anImage, pgmImage *cImage, int multi);

int isBinary(unsigned short *magic_Number);

void checkEOF(int binary, char* fileName, FILE *inputFile, pgmImage *anImage, pgmImage *cImage, 
int multi);

void checkFileType(pgmImage *anImage, char *fileName, int binary);
