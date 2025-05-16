#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void test_file_access(const char *filename) {
    printf("\nTesting access to %s:\n", filename);
    printf("Read access: %s\n", access(filename, R_OK) == 0 ? "Yes" : "No");
    printf("Write access: %s\n", access(filename, W_OK) == 0 ? "Yes" : "No");
    printf("Execute access: %s\n", access(filename, X_OK) == 0 ? "Yes" : "No");
}

int main() {
    // Создаем временный файл
    FILE *fp = fopen("tempfile.txt", "w");
    if (fp == NULL) {
        perror("Failed to create file");
        return 1;
    }
    fprintf(fp, "Test content\n");
    fclose(fp);
    
    printf("Original permissions:\n");
    system("ls -l tempfile.txt");
    test_file_access("tempfile.txt");
    
    // Меняем владельца и права
    system("sudo chown root:root tempfile.txt");
    system("sudo chmod 600 tempfile.txt");
    
    printf("\nAfter changing owner and permissions:\n");
    system("ls -l tempfile.txt");
    test_file_access("tempfile.txt");
    
    // Возвращаем права
    system("sudo chown $(id -u):$(id -g) tempfile.txt");
    system("chmod 644 tempfile.txt");
    
    printf("\nAfter restoring permissions:\n");
    system("ls -l tempfile.txt");
    test_file_access("tempfile.txt");
    
    // Удаляем файл
    remove("tempfile.txt");
    
    return 0;
}