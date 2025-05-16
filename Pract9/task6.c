#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void test_directory(const char *path) {
    printf("\nTesting directory: %s\n", path);
    printf("Contents and permissions:\n");
    char command[256];
    snprintf(command, sizeof(command), "ls -ld %s", path);
    system(command);
    snprintf(command, sizeof(command), "ls -l %s | head -n 5", path);
    system(command);
    
    // Проверяем доступ
    printf("\nAccess tests:\n");
    printf("Read access: %s\n", access(path, R_OK) == 0 ? "Yes" : "No");
    printf("Write access: %s\n", access(path, W_OK) == 0 ? "Yes" : "No");
    printf("Execute access: %s\n", access(path, X_OK) == 0 ? "Yes" : "No");
    
    // Пытаемся создать временный файл
    char testfile[256];
    snprintf(testfile, sizeof(testfile), "%s/testfile_%d", path, getpid());
    printf("\nTrying to create %s:\n", testfile);
    FILE *fp = fopen(testfile, "w");
    if (fp) {
        fprintf(fp, "Test content\n");
        fclose(fp);
        printf("File created successfully\n");
        remove(testfile);
    } else {
        perror("Failed to create file");
    }
}

int main() {
    test_directory(getenv("HOME"));
    test_directory("/usr/bin");
    test_directory("/etc");
    
    return 0;
}