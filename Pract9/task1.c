#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    FILE *fp;
    char line[1024];
    uid_t current_uid = getuid();
    struct passwd *current_user = getpwuid(current_uid);
    
    printf("Current user: %s (UID: %d)\n", current_user->pw_name, current_uid);
    printf("Regular users (UID >= 1000, excluding yourself):\n");

    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("Failed to run getent");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        struct passwd pwd;
        struct passwd *result;
        char buffer[1024];
        
        if (getpwnam_r(line, &pwd, buffer, sizeof(buffer), &result) != 0 || result == NULL) {
            continue;
        }
        
        if (pwd.pw_uid >= 1000 && pwd.pw_uid != current_uid) {
            printf("User: %s, UID: %d, Shell: %s\n", pwd.pw_name, pwd.pw_uid, pwd.pw_shell);
        }
    }

    pclose(fp);
    return 0;
}