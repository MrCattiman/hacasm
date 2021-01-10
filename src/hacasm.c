#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "hacal_asmlib.h"

char**       cset;
char**       vset;
char*        input;
char*        output;
unsigned int inputlen;

void previewSet() {
	printf("----------\nConsonants\n----------\n\nHex | Value\n--- | -----\n");
	for (int i = 0; i < 15; i++) {
		printf("%3x | %s\n",i+1,cset[i]);
	};
	printf("\n------\nVowels\n------\n\nHex | Value\n--- | -----\n");
	for (int i = 0; i < 15; i++) {
		printf("%3x | %s\n",i+1,vset[i]);
	};
};

void setIn(char* path) {
	if (input != 0) free(input);
	FILE* inputFile = fopen(path,"r");
	if (inputFile == 0) {
		fprintf(stderr,"Null input file pointer.\n");
		exit(1);
	};
	fseek(inputFile, 0L, SEEK_END);
	inputlen = ftell(inputFile);
	rewind(inputFile);
	input = (char*)malloc(inputlen);
	fread(input, inputlen, 1, inputFile);
	fclose(inputFile);
};

void write(char* path) {
	FILE* writeto = fopen(path,"w");
	fputs(output, writeto);
	fclose(writeto);
};

int main(int args, char *arg[]) {
	if (args < 3) {
		printf("hacasm <consonant set path> <vowel set path> [<parameter> (path)]\n\n-i <file path> or --input <file path>\n	Set the input file, must come before -t or -d.\n-t <file path> or --text <file path>\n	Output a basic HACAL text file.\n-d <file path> or --dict <file path>\n	Output a dictionary.\n-h <file path> or --headless <file path>\n	generate the selected file(s) without a header.\n--preview-set\n	Preview/test the set you would use.");
		return 0;
	};
	cset = hacal_loadSet(arg[1]);
	vset = hacal_loadSet(arg[2]);
	if (args == 3) previewSet();
	for (int i = 3; i < args; i++) {
		if ( strcmp(arg[i], "--preview-set") == 0) {
			previewSet();
		};
		if ( strcmp(arg[i], "--input") == 0) {
			setIn(arg[++i]);
		};
		if ( strcmp(arg[i], "--text") == 0 ) {
			output = hacal_asm(cset, vset, input, inputlen);
			write(arg[++i]);
			free(output);
		};
	};
};
