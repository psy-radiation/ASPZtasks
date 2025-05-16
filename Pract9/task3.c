#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    // Создаем файл как обычный пользователь
    system("echo 'Original content' > user_file.txt");
    system("ls -l user_file.txt");
    
    // Копируем файл как root
    system("sudo cp user_file.txt root_copy.txt");
    system("sudo chown root:root root_copy.txt");
    system("sudo cp root_copy.txt ~/user_copy.txt");
    system("sudo chown $(id -u):$(id -g) ~/user_copy.txt");
    
    printf("\nFile ownership after operations:\n");
    system("ls -l user_file.txt root_copy.txt ~/user_copy.txt");
    
    // Пытаемся изменить файл
    printf("\nTrying to modify files:\n");
    system("echo 'User modification' >> user_file.txt");
    system("echo 'User modification' >> root_copy.txt 2>&1");
    system("echo 'User modification' >> ~/user_copy.txt");
    
    // Пытаемся удалить файлы
    printf("\nTrying to delete files:\n");
    system("rm -v user_file.txt");
    system("rm -v root_copy.txt 2>&1");
    system("rm -v ~/user_copy.txt");
    
    // Убираем временные файлы
    system("sudo rm -f root_copy.txt ~/user_copy.txt");
    
    return 0;
}