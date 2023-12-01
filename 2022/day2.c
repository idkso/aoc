#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <err.h>
#include "common.h"

int
solve1(char x, char y)
{
	x = (x - 'A') + 1;
	y = (y - 'X') + 1;

	if (x == y) return y + 3;
	if (x == y-1) return y + 6;
	if (y == x-2) return y + 6;
	return y;
}

int
solve2(signed char x, signed char y)
{
	int points;
	x = (x - 'A');
	y = (y - 'X');

	points = y * 3;
	points += (x + ((y + 2) % 3)) % 3;
	return points + 1;
}

int
main(void)
{
	int total1 = 0;
	int total2 = 0;
	char *line;
	int size;
	struct file f = {0};
	
	read_file("day2.input", &f);

	for (;;) {
		read_line(&f, &line, &size);
		if (size <= 0) {
			break;
		}
		total1 += solve1(line[0], line[2]);
		total2 += solve2(line[0], line[2]);
	}

	printf("total1: %d\n", total1);
	printf("total2: %d\n", total2);

	file_deinit(&f);
}
