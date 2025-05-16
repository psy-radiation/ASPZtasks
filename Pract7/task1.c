#include <stdio.h>

int main() {
    FILE *fp = popen("rwho | more", "r");
    if (!fp) {
        perror("popen failed");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    pclose(fp);
    return 0;
}
