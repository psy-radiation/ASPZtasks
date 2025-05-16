#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    // Создаем временный файл с заданными байтами
    int fd = open("testfile.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }
    
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    write(fd, data, sizeof(data));
    close(fd);
    
    // Теперь читаем как в задании
    fd = open("testfile.bin", O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(1);
    }
    
    unsigned char buffer[4] = {0};
    lseek(fd, 3, SEEK_SET);
    read(fd, buffer, 4);
    
    printf("Buffer contents: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    
    close(fd);
    return 0;
}