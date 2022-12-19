/*pgmImage structure for encapsulation*/
typedef struct _pgmImage {
	unsigned char magic_number[2];
    	unsigned short *magic_Number;
	unsigned int width, height, maxGrey;
	int **imageData;
	int binary;
} pgmImage;

/*Interfaces for functions*/
pgmImage initPgmImage();
void removePgmImage(pgmImage *anImage);

void pgmRead(char *fileName, pgmImage *anImage, pgmImage *cImage, int multi);
void pgmWrite(char *fileName, pgmImage *anImage, pgmImage *cImage, int multi,
int dynamic);

void copyHeaderData(pgmImage *image, pgmImage *anImage, int width, int height);
void allocateMemory(pgmImage *anImage, pgmImage *cImage, 
FILE *inputFile, int fileExists, int multi);
