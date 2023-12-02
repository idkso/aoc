#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "common.h"

int
solve1(char *line, int size)
{
	int f, l, b = 0, n;

	for (int i = 0; i < size; i++) {
		if (!isdigit(line[i])) continue;
		n = line[i]-'0';
		if (b) l = n; else f = n;
		b++;
	}

	if (b == 1) return (f*10)+f;
	else return (f*10)+l;
}

struct text {
	char *ptr;
	int size, off;
};

const char *numbers[] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	NULL,
};

int
matches(struct text *txt, const char *arr[])
{
	int len;
	for (int i = 0; arr[i] != NULL; i++) {
		len = strlen(arr[i]);
		if (memcmp(txt->ptr+txt->off, arr[i], len) == 0) {
			txt->off += len;
			return i;
		}
	}
	return -1;
}

int
getdigit(struct text *txt)
{
	int out;
	if (isdigit(txt->ptr[txt->off])) {
		out = txt->ptr[txt->off]-'0';
		txt->off++;
		return out;
	}

	if ((out = matches(txt, numbers)) == -1) {
		return -1;
	}

	return out;
}

int
solve2(char *line, int size)
{
	int f, l, b = 0, n;
	struct text txt = {
		.ptr = line,
		.size = size,
		.off = 0,
	};
	while (txt.off < txt.size) {
		n = getdigit(&txt);
		if (n == -1) {
			txt.off++;
			continue;
		}
		if (b) l = n; else f = n;
		b++;
	}

	if (b == 1) return (f*10)+f;
	else return (f*10)+l;
}

int
main(void)
{
	int size, ans1 = 0, ans2 = 0;
	char *line;
	struct file f = {0};
	struct timespec now, l8r;

	clock_gettime(CLOCK_REALTIME, &now);

	read_file("day1.input", &f);

	for (;;) {
		read_line(&f, &line, &size);
		if (size <= 0) {
			break;
		}
		ans1 += solve1(line, size);
		ans2 += solve2(line, size);
	}
	printf("answer 1: %d\n", ans1);
	printf("answer 2: %d\n", ans2);

	file_deinit(&f);
	clock_gettime(CLOCK_REALTIME, &l8r);
	printf("took %ldns\n", l8r.tv_nsec-now.tv_nsec);
	return 0;
}
