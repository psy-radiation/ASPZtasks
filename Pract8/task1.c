#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    // Устанавливаем мягкий лимит на размер файла в 512 байт
    struct rlimit rl = {512, 512};
    setrlimit(RLIMIT_FSIZE, &rl);

    int fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }
    
    char buffer[1024];
    ssize_t nbytes = sizeof(buffer);
    ssize_t count = write(fd, buffer, nbytes);
    
    if (count == -1) {
        perror("write error");
    }
    
    printf("Requested to write: %zd, actually written: %zd\n", nbytes, count);
    
    close(fd);
    return 0;
}