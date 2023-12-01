#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <err.h>
#include "common.h"


int
main(void)
{
	char *line;
	int size;
	struct file f = {0};
	struct array arr = {0};
	
	int cals = 0, ret;
	int done = 0;
	const char *errstr;

	array_init(&arr, 100);
	read_file("day1.input", &f);

	for (;;) {
		read_line(&f, &line, &size);
		if (size <= 0) {
			array_append(&arr, cals);
			if (size == -1) break;
			cals = 0;
			continue;
		};
		line[size] = 0;
		ret = (int)strtonum(line, 0, INT_MAX, &errstr);
		if (ret == 0 && errstr != NULL) {
			err(1, "strtonum: '%s'", line);
		}
		cals += ret;
	}

	qsort(arr.values, arr.len, 
			sizeof(int), greatest_to_least);
	
	printf("most calories on 1 elf: %d\n", arr.values[0]);
	printf("last 3 elves calories: %d\n",
					arr.values[0] + arr.values[1] + arr.values[2]);
	array_deinit(&arr);
	file_deinit(&f);
}
