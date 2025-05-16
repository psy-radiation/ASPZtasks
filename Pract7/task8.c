#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char answer;

    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;

        printf("Видалити файл %s? (y/n): ", entry->d_name);
        scanf(" %c", &answer);
        if (answer == 'y') {
            unlink(entry->d_name);
            printf("Видалено.\n");
        }
    }

    closedir(dir);
    return 0;
}
