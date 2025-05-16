#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char answer;

    while ((entry = readdir(dir))) {
        if (strstr(entry->d_name, ".c")) {
            printf("Надати читання файлу %s? (y/n): ", entry->d_name);
            scanf(" %c", &answer);
            if (answer == 'y') {
                chmod(entry->d_name, S_IRUSR | S_IRGRP | S_IROTH);
                printf("Дозвіл надано.\n");
            }
        }
    }

    closedir(dir);
    return 0;
}
