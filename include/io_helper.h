#ifndef IO_HELPER_H
#define IO_HELPER_H

/**
 * @brief Validates a file argument.
 * 
 * @param fp File pointer to opened file to validate against.
 * 
 * @return 1 on success, else 0.
 */
int validate_file(FILE * fp);

#endif
