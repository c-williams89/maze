#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>

typedef struct graph_data {
	uint16_t rows;
	uint16_t cols;
} graph_data;

int validate_file(FILE * fp)
{
	int exit_status = 0;
	if (!fp) {
		fprintf(stderr, "validate_file: Invalid file pointer - NULL\n");
		goto EXIT;
	}

	struct stat path_stat;
	int fileno(FILE * fp);
	int fd = fileno(fp);

	// Tests that fstat does not fail
	if (-1 == fstat(fd, &path_stat)) {
		perror("validate_file: Unable to retrieve file information");
		errno = 0;
		goto EXIT;
	}

	if (S_ISREG(path_stat.st_mode)) {
		if (0 < path_stat.st_size) {
			exit_status = 1;
		}
	}

 EXIT:
	return exit_status;
}
