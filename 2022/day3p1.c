#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <err.h>
#include "common.h"

int
solve(char *line, int size)
{
	int out = 0;
	char *f = line;
	char *s = line+(size / 2);
	char set[256] = {0};
	for (int i = 0; i < (size / 2); i++) {
		set[f[i]] = 1;
	}
	for (int i = 0; i < (size / 2); i++) {
		if (!set[s[i]]) continue;
		if (s[i] >= 'a') {
			out += (s[i] - 'a') + 1;
		} else {
			out += (s[i] - 'A') + 27;
		}
		set[s[i]] = 0;
	}
	return out;
}

int
main(void)
{
	struct file f = {0};
	char *line;
	int size, total = 0;
	
	read_file("day3.input", &f);

	for (;;) {
		read_line(&f, &line, &size);
		if (size <= 0) {
			break;
		}
		total += solve(line, size);
	}

	printf("total: %d\n", total);

	file_deinit(&f);
}
