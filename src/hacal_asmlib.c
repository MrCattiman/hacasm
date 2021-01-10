#include "stdlib.h"
#include "stdio.h"
#include "errno.h"
#include "ctype.h"
#include "string.h"

typedef struct syllable {
	char c:4;
	char v:4;
} syl;

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
};

/* The sets should be loaded in memory as an array with pointers to arrays of chars */
char* hacal_asm(char** cset, char** vset, char* inbuf, unsigned int inbuflen) {
	char buf[0xff];
	syl           syllable;
	char          buft   = 0;
	unsigned int  oi     = 0;
	unsigned char parity = 0;
	char*         outbuf = (char*)calloc(inbuflen, sizeof(char));
	if (outbuf == 0) {
		fprintf(stderr, "Failed to allocate memory for a buffer.\n");
		exit(2);
	};
	for (unsigned int i = 0; i < inbuflen; i++) {
		if (inbuf[i] == '\n' || inbuf[i] == ' ' || inbuf[i] == '-') {
			buft         = 0;
			buf[0]       = 0;
			outbuf[oi++] = 0;
		} else {
			buf[buft++] = tolower(inbuf[i]);
		};
		if(buft > 0xff) {
			fprintf(stderr, "Buffer overflow!\nDetails:\n  Buffer: %s\n  Buffer length: %u\n", buf, buft);
			exit(1);
		};
		if(buft > 0) { 
			if (parity) {
			for (unsigned int ci = 16; --i;) {
				if (strcmp(buf, vset[ci]) == 0) {
					syllable.v = ci + 1;
					parity = 0;
					break;
				};
			};
			} else {
			for (unsigned int ci = 16; --i;) {
				if (strcmp(buf, cset[ci]) == 0) {
					syllable.c = ci + 1;
					parity = 1;
					break;
				};
			};
			};
		};
	};
	return outbuf;
};
