#include "stdlib.h"
#include "stdio.h"
#include "errno.h"
#include "ctype.h"
#include "string.h"

char** hacal_loadSet(char* filepath) {
	FILE* file = fopen(filepath,"r");
	char** set = malloc(sizeof(char*) * 15);
	for(unsigned char i = 0; i < 16; i++) {
		set[i] = malloc(sizeof(char) * 11);
		set[i][5] = 0;
	};
	char i = 0;
	unsigned char bufi;
	char get;
	loop:
		if (i == 15) goto endloop;
		get = fgetc(file);
		if (get == '\n') {
			set[i][bufi] = 0;
			bufi = 0;
			i++;
			goto loop;
		};
		if (get != EOF) {
			if (bufi < 10) {
				set[i][bufi] = get;
				bufi++;
			};
	 		goto loop;
		};
	endloop:
	return set;
}

/* The sets should be loaded in memory as an array with pointers to arrays of chars */
char* hacal_asm(char** cset, char** vset, char* inbuf, unsigned int inbuflen) {
	char buf[0xff];
	char          syl    = 0;
	char          buft   = 0;
	unsigned int  oi     = 0;
	char*         outbuf = (char*)calloc(inbuflen, sizeof(char));
	char          parity = 0;
	if (outbuf == 0) {
		fprintf(stderr, "Failed to allocate memory for a buffer.\n");
		exit(2);
	};
	return outbuf;
}
