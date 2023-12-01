#ifndef AOC_COMMON_H
#define AOC_COMMON_H
struct file {
	int fd, size, p;
	char *map;
};

void read_file(const char *path, struct file *f);
void read_line(struct file *f, char **linep, int *size);
void file_deinit(struct file *f);

struct array {
	int *values;
	int len, size;
};

void array_init(struct array *arr, int size);
void array_append(struct array *arr, int value);
void array_deinit(struct array *arr);
int greatest_to_least(const void *, const void *);
#endif
