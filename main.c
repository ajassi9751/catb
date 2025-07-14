#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void printBianary (unsigned char byte) {
	int i;
	for (i = 7; i>=0;--i) {
		printf("%d",(byte>>i)&1);
	}
}


int main (int argc, char *argv[]) {
	int opt;
	char flags[] = {'i'};
	bool flagstates[] = {false};
	bool vFlag;
	bool fArg[argc];
	int flgdArgs=0;
	fArg[1] = false;
	for (int i=1;i<argc;++i) {
		if (argv[i][0]=='-') {
			flgdArgs++;
			fArg[i] = true;
			for (int s=1;s<strlen(argv[i]);++s) {
				vFlag = false;
				for (int a=0;a<sizeof(flags)/sizeof(flags[0]);++a) {
					if (argv[i][s]==flags[a]) {
						flagstates[a] = true;
						vFlag = true;
					}
				}
				if (!vFlag) {
					printf("Invalid flag");
					return EXIT_FAILURE;
				}
			}
		}
		else {
			fArg[i] = false;
		}
	}	
	if (argc<2+flgdArgs) {
		printf("Expected a valid filename or path");
		return EXIT_FAILURE;
	}
	FILE *readee;
	if (!flagstates[0]) {
		unsigned char byte;
		for (int c=1;c<argc;++c) {	
			if (fArg[c]) {
				continue;	
			}
			readee = fopen(argv[c],"rb");
			if (readee == NULL) {
				printf("Unable to open file");
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
		for (int d=1;d<argc;++d) {
			if (fArg[d]) {
				continue;	
			}
			readee = fopen(argv[d],"rb");	
			if (readee == NULL) {
				printf("Unable to open file");
				return EXIT_FAILURE;
			}	
			fseek(readee,0,SEEK_END);
			long size = ftell(readee);
			int *data = (int *)malloc(size);
			if (data==NULL) {
				printf("Memory allocation failed");
				free(data);
				fclose(readee);
				return EXIT_FAILURE;
			}
			rewind(readee);
			size_t datasz = fread(data,sizeof(int),size,readee);
			if (datasz != size) {
				if (ferror(readee)) {
					printf("Error reading file");
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
