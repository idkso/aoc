#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#include "common.h"

struct game {
	int num;
	int red, green, blue;
};

int
offshit(char *ptr)
{
	int i = 0;
	while (true) {
		if (*(ptr+i) == 0) return i;
		if (*(ptr+i) == ',') return i;
		if (*(ptr+i) == ';') return i;
		i++;
	}
}

void
parse_cubes(char *line, char *ep, struct game *game)
{
	char *p, *p2;
	int num, off, off2;

	p = line;

	while ((p = strchr(p, '='))) {
		for (off = 0; p[off] != ' '; off--) {
			if (p+off == line) {
				off--;
				break;
			}
		}
		off++;
		p2 = p+1;
		off2 = offshit(p2);
		p2[off2] = 0;
		num = strtonum(p2, 0, 100, NULL);
		p2 += off2+2;

		if (p >= ep) return;

		if (!memcmp(p+off, "red", 3)) {
			if (game->red < num) game->red = num;
		} else if (!memcmp(p+off, "green", 5)) {
			if (game->green < num) game->green = num;
		} else if (!memcmp(p+off, "blue", 4)) {
			if (game->blue < num) game->blue = num;
		}
		p = p2;
	}
}

int
solve1(char *line, int size)
{
	char *p;
	int ret;
	struct game game = {0};
	line[size] = 0;
	p = strchr(line, ' ');
	*p = 0;
	game.num = strtonum(line, 0, 100, NULL);
	line = p+1;
	parse_cubes(line, line+size, &game);

	return game.red * game.green * game.blue;
}

int
main(void)
{
	int size, ans1 = 0;
	char *line;
	struct file f = {0};
	struct timespec now, l8r;

	clock_gettime(CLOCK_REALTIME, &now);

	read_file("day2.input.pp", &f);

	for (;;) {
		read_line(&f, &line, &size);
		if (size <= 0) {
			break;
		}
		ans1 += solve1(line, size);
	}
	printf("answer 1: %d\n", ans1);

	file_deinit(&f);
	clock_gettime(CLOCK_REALTIME, &l8r);
	printf("took %ldns\n", l8r.tv_nsec-now.tv_nsec);
	return 0;
}
