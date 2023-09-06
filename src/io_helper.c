#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>




int validate_file(FILE *fp) {
        struct stat path_stat;
        int exit_status = 0;
        int fd = fileno(fp);  

        // Tests that fstat does not fail
        if (-1 == fstat(fd, &path_stat)) {
                perror("validate_file: Unable to retrieve file information");
                errno = 0;
                goto EXIT;
        }

        // Tests the case where stdin, stdout, or stderr have been passed.
        if (3 > fd) {
                fprintf(stderr, "validate_file: Invalid stream. Must be file.\n");
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