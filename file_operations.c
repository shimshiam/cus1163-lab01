#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    int fd;
    ssize_t bytes_written;

    printf("Creating file: %s\n", filename);
    printf("Content to write: %s\n", content);

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    if (fd == -1){
    perror("Error: Cannot open file\n");
    return -1;
    }

    printf("File opened, the descriptor value is: %d\n", fd);

    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("Error: Failed to write file\n");
        close(fd);
        return -1;
    }

    printf("Successfully wrote %zd bytes to %s.\n", bytes_written, filename);

    
    if (close(fd) == -1) {
        perror("Error: Cannot close file\n");
        return -1;
    }

    printf("File closed successfully.\n");
    return 0;
}

int read_file_contents(const char *filename) {

    int fd;
    char buffer[1024];
    ssize_t bytes_read;

    printf("Reading: %s\n", filename);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error: File cannot be opened\n");
        return -1;
    }

    printf("File opened successfully: %d\n", fd);
    printf("|START OF FILE CONTENTS|\n");

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
      buffer[bytes_read] = '\0';\
      printf("%s", buffer);
      }

    if (bytes_read == -1) {
        perror("Error: Cannot read file\n");
        close(fd);
        return -1;
    }

    printf("\n|END FILE CONTENTS|\n");
  
    
    if (close(fd) == -1) {
        perror("Error closing file\n");
        return -1;
    }

    printf("File closed successfully.\n");
}
