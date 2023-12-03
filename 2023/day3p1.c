#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "common.h"

char buf[140][140];

struct place {
	int value;
	int x, y, len;
};

struct solution {
	struct place symbols[140 * 140];
	struct place numbers[140 * 140];
	int nsym, nnum;
	int final;
};

static struct solution s = {0};

void 
grab_symbols(void)
{
	for (int y = 0; y < 140; y++) {
		for (int x = 0; x < 140; x++) {
			if (isdigit(buf[y][x]) || buf[y][x] == '.') continue;
			s.symbols[s.nsym].value = buf[y][x];
			s.symbols[s.nsym].x = x;
			s.symbols[s.nsym].y = y;
			s.symbols[s.nsym].len = 1;
			s.nsym++;
		}
	}
}

void
grab_numbers(void)
{
	int tmp;
	for (int y = 0; y < 140; y++) {
		for (int x = 0; x < 140; x++) {
			tmp = 0;
			while (isdigit(buf[y][x+tmp])) tmp++;
			if (tmp == 0) continue;
			buf[y][x+tmp] = 0;
			s.numbers[s.nnum] = (struct place){
				.x = x,
				.y = y,
				.len = tmp,
				.value = strtonum(buf[y]+x, 0, 10000, NULL),
			};
			x += tmp;
			s.nnum++;
		}
	}
}

int
close_enough(struct place x, struct place y)
{
	if (x.y == y.y+1 || x.y == y.y-1 || x.y == y.y) {
		if (x.x < y.x && x.x+x.len >= y.x) return 0;
		if (x.x-1 == y.x || x.x == y.x) {
			return 0;
		}
	}
	return 1;
}

void
add_adjacent_numbers(struct place p)
{
	for (int i = 0; i < s.nnum; i++) {
		if (close_enough(s.numbers[i], p) == 1) {
			continue;
		}
		s.final += s.numbers[i].value;
	}
}

int
solve(void)
{
	grab_symbols();
	grab_numbers();

	for (int i = 0; i < s.nsym; i++) {
		add_adjacent_numbers(s.symbols[i]);
	}

	return s.final;
}

int
main(void)
{
	int size, ans;
	char *line;
	struct file f = {0};
	struct timespec now, l8r;

	clock_gettime(CLOCK_REALTIME, &now);

	read_file("day3.input", &f);

	for (int i = 0; i < 140; i++) {
		read_line(&f, &line, &size);
		if (size <= 0) {
			break;
		}
		memcpy(buf[i], line, size);
	}

	ans = solve();
	printf("answer: %d\n", ans);

	file_deinit(&f);
	clock_gettime(CLOCK_REALTIME, &l8r);
	printf("took %ldns\n", l8r.tv_nsec-now.tv_nsec);
	return 0;
}
