#include <stdlib.h>
#include <stdio.h>

int main(int args, char *arg[]) {
	if (args < 1) {
		printf("-t <file path> or --text <file path>\n	Output a basic HACAL text file.\n-d <file path> or --dict <file path>\n	Output a dictionary.\n-o <file path> or --out\n	output to a file rather than stdout.\n--headless <filepath>\n	generate the file(s) without a header.");
		return 0;
	};
};
