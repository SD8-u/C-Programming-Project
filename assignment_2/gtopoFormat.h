/*pgmImage structure for encapsulation*/
typedef struct _gtopoModel {
	unsigned int width, height;
	short **elevationData;
} gtopoModel;

/*Interfaces for functions*/
gtopoModel initGtopoModel(int width, int height, gtopoModel *cDem,
int multi);
void removeGtopoModel(gtopoModel *dem);

void gtopoRead(char *fileName, gtopoModel *dem, gtopoModel *cDem,
int multi);
void gtopoWrite(char *fileName, gtopoModel *dem, gtopoModel *cDem, 
int multi, int dynamic);

void allocateMemory(gtopoModel *dem, gtopoModel *cDem, 
FILE *inputFile, int fileExists, int multi);
