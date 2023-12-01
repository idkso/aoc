#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "common.h"

// |---------------------------|
// | file io                   |
// |---------------------------|

void
read_file(const char *path, struct file *f)
{
	int fd;
	char *map;
	struct stat st;

	fd = open(path, O_RDONLY);
	if (fd == -1) {
		err(1, "opening file '%s'", path);
	}
	if (fstat(fd, &st) == -1) {
		err(1, "ftat on file '%s'", path);
	}
	map = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, 
				MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED) {
		err(1, "mmap on file '%s'", path);
	}
	f->fd = fd;
	f->map = map;
	f->size = st.st_size;
	close(f->fd);
}

void
read_line(struct file *f, char **linep, int *size)
{
	if (f->p == f->size) {
		*size = -1;
		return;
	}
	*linep = f->map+f->p;
	int oldp = f->p;
	while (f->p < f->size && f->map[f->p] != '\n') f->p++;
	*size = f->p-oldp;
	f->p++;
}


void
file_deinit(struct file *f)
{
	munmap(f->map, f->size);
}
// |---------------------------|
// | array data structure      |
// |---------------------------|

void
array_resize(struct array *arr, int size)
{
	arr->values = reallocarray(arr->values, size, sizeof(int));
	if (arr->values == NULL) {
		err(1, "resizing array");
	}
	arr->size = size;
}

void
array_init(struct array *arr, int size)
{
	arr->len = 0;
	array_resize(arr, size);
}

void
array_append(struct array *arr, int value)
{
	if (arr->len == arr->size) {
		array_resize(arr, arr->size*2);
	}
	arr->values[arr->len++] = value;
}

void
array_deinit(struct array *arr)
{
	arr->len = 0;
	arr->size = 0;
	free(arr->values);
}

int
greatest_to_least(const void *xp, const void *yp) {
	const int x = *(int*)xp;
	const int y = *(int*)yp;
	return y - x;
}
