#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_dir(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char new_path[1024];

    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;

        snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
        printf("%s\n", new_path);

        struct stat st;
        stat(new_path, &st);
        if (S_ISDIR(st.st_mode)) {
            list_dir(new_path);
        }
    }

    closedir(dir);
}

int main() {
    list_dir(".");
    return 0;
}
