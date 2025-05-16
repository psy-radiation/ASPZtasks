#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fd1, fd2, fd3;
    
    // Создаем файл для вывода
    fd1 = open("output1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1) {
        perror("open failed");
        exit(1);
    }
    
    // Используем dup() - система выбирает новый дескриптор
    fd2 = dup(STDOUT_FILENO);  // Сохраняем оригинальный stdout
    dup2(fd1, STDOUT_FILENO);  // Перенаправляем stdout в файл
    
    printf("This goes to output1.txt\n");
    
    // Восстанавливаем stdout
    dup2(fd2, STDOUT_FILENO);
    close(fd2);
    
    // Теперь используем dup2() с явным указанием дескриптора
    fd3 = open("output2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd3 == -1) {
        perror("open failed");
        exit(1);
    }
    
    // Перенаправляем stdout (дескриптор 1) в fd3
    dup2(fd3, STDOUT_FILENO);
    printf("This goes to output2.txt\n");
    
    // Закрываем файловые дескрипторы
    close(fd1);
    close(fd3);
    
    // Возвращаем вывод на консоль
    dup2(1, STDOUT_FILENO);
    printf("Output restored to console\n");
    
    return 0;
}