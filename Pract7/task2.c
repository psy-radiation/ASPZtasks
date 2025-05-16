#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char *types = (S_ISDIR(mode)) ? "d" : "-";
    printf("%s%c%c%c%c%c%c%c%c%c ", types,
        (mode & S_IRUSR) ? 'r' : '-', (mode & S_IWUSR) ? 'w' : '-', (mode & S_IXUSR) ? 'x' : '-',
        (mode & S_IRGRP) ? 'r' : '-', (mode & S_IWGRP) ? 'w' : '-', (mode & S_IXGRP) ? 'x' : '-',
        (mode & S_IROTH) ? 'r' : '-', (mode & S_IWOTH) ? 'w' : '-', (mode & S_IXOTH) ? 'x' : '-');
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat info;

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &info);
        print_permissions(info.st_mode);
        printf("%lu %s %s %ld %s", 
            info.st_nlink,
            getpwuid(info.st_uid)->pw_name,
            getgrgid(info.st_gid)->gr_name,
            info.st_size,
            ctime(&info.st_mtime)
        );
        printf(" %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
