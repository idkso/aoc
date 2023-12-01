#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <err.h>
#include "common.h"

int
solve(char *lines[3], int sizes[3])
{
	char *line;
	int size, out = 0;
	char sets[3][256] = {0};

	for (int i = 0; i < 3; i++) {
		line = lines[i];
		size = sizes[i];
		for (int j = 0; j < size; j++) {
			sets[i][line[j]] = 1;
		}
	}

	for (int i = 0; i < 256; i++) {
		if (sets[0][i] && sets[1][i] && sets[2][i]) {
			if (i < 'a') {
				out += (i-'A')+27;
			} else {
				out += (i-'a')+1;
			}
		}
	}
	return out;
}

int
main(void)
{
	struct file f = {0};
	char *lines[3];
	int sizes[3], total = 0;
	
	read_file("day3.input", &f);

	for (;;) {
		for (int i = 0; i < 3; i++) {
			read_line(&f, &lines[i], &sizes[i]);
			if (sizes[i] <= 0) {
				break;
			}
		}
		total += solve(lines, sizes);
		if (f.p == f.size) break;
	}

	printf("total: %d\n", total);

	file_deinit(&f);
}
