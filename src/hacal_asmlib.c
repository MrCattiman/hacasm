#include "stdlib.h"
#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "hacal_asmlib.h"

/* The sets should be loaded in memory as an array with pointers to arrays of chars */
syl* hacal_asm(char** cset, char** vset, char* inbuf, unsigned int inbuflen) {
	char buf[0xff];
	syl           syllable;
	char          buft   = 0;
	unsigned int  oi     = 0;
	unsigned char parity = 0;
	syl*          outbuf = (syl*)calloc(inbuflen, sizeof(char));
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
};
