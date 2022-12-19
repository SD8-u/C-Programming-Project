//interfaces for functions in gtopoError

void checkGtopoData(short *data, FILE *inputFile, gtopoModel *dem, gtopoModel *cDem, int row, 
int fileExists, int multi);
void check2DGtopoData(short **data, FILE *inputFile, gtopoModel *dem, gtopoModel *cDem, 
int fileExists, int multi);

void checkElevationValue(int count, FILE *inputFile, char *fileName, gtopoModel *dem, 
gtopoModel *cDem, int multi);

void checkGtopoAlloc(gtopoModel *dem, gtopoModel *cDem, int multi);

void checkEOF(char* fileName, FILE *inputFile, gtopoModel *dem, gtopoModel *cDem,
int multi);
