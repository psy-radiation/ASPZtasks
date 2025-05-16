#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    printf("Current user information:\n");
    system("whoami");
    system("id");
    
    // Альтернативный способ через системные вызовы
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    
    printf("\nDetailed user info:\n");
    printf("Username: %s\n", pw->pw_name);
    printf("User ID: %d\n", pw->pw_uid);
    printf("Group ID: %d\n", pw->pw_gid);
    printf("Home directory: %s\n", pw->pw_dir);
    printf("Shell: %s\n", pw->pw_shell);
    
    return 0;
}