typedef struct syllable {
	char c:4;
	char v:4;
} syl;

extern syl* hacal_asm(char* cset, char* vset, char* inbuf, char* outbuf);
