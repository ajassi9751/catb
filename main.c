#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	char path[256];
	scanf("%255s", path);
	FILE *readee;
	readee = fopen(path,"rb");
	
	fseek(readee,0,SEEK_END);
	long size = ftell(readee);
	rewind(readee);
	int data[size];
	fread(data,sizeof(int),size,readee);
	fclose(readee);
	int i;
	for(i=0;i<size;++i) {
		printf("%d", data[i]);
	}
	return 1;
}
