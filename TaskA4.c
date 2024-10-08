#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FILENAME "example.txt"
#define TEXT "Hello, POSIX World!\n"

int main() {

    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    if (write(fd, TEXT, strlen(TEXT)) == -1) {
        perror("Failed to write to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Failed to read from file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    buffer[bytesRead] = '\0';
    printf("Read from file: %s", buffer);
    close(fd);
    unlink(FILENAME);
    return 0;
}