#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void printBianary (unsigned char byte) {
	int i;
	for (i = 7; i>=0;--i) {
		printf("%d",(byte>>i)&1);
	}
}


int main (int argc, char *argv[]) {
	int opt;
	bool isInteger = false;	
	int i;
	for (i=1;i<argc;++i) {
			
	}	
	if (argc<2) {
		perror("Expected a valid filename or path");
		return EXIT_FAILURE;
	}
	FILE *readee;
	if (!isInteger) {
		unsigned char byte;
		for (i=1;i<argc;++i) {	
			readee = fopen(argv[i],"rb");
			if (readee == NULL) {
				perror("Unable to open file");
					return EXIT_FAILURE;
			}
			while (fread(&byte,sizeof(unsigned char),1,readee) == 1) {
				printBianary(byte);
			}
			printf("\n");
			fclose(readee);
		}
	}
	else {
		for (i=1;i<argc;++i) {
			readee = fopen(argv[i],"rb");	
			if (readee == NULL) {
				perror("Unable to open file");
				return EXIT_FAILURE;
			}	
			fseek(readee,0,SEEK_END);
			long size = ftell(readee);
			int *data = (int *)malloc(size);
			if (data==NULL) {
				perror("Memory allocation failed");
				free(data);
				fclose(readee);
				return EXIT_FAILURE;
			}
			rewind(readee);
			size_t datasz = fread(data,sizeof(int),size,readee);
			if (datasz != size) {
				if (ferror(readee)) {
					perror("Error reading file");
			}
				else {
					printf("Possible file reading error or size conflict");
				}
				fclose(readee);
				free(data);
				return EXIT_FAILURE;
			}
			fread(data,sizeof(int),size,readee);
			for (int i2=0;i2<size;++i2) {
				printf("%d",data[i2]);
			}
			printf("\n");
			fclose(readee);
			free(data);
			data = NULL;
		}
	}
	return EXIT_SUCCESS;
}
