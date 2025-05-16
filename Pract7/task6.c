#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX 1000

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char *dirs[MAX];
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        stat(entry->d_name, &st);
        if (S_ISDIR(st.st_mode) && entry->d_name[0] != '.') {
            dirs[count++] = strdup(entry->d_name);
        }
    }

    qsort(dirs, count, sizeof(char *), cmp);
    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    closedir(dir);
    return 0;
}
