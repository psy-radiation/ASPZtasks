#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Використання: %s <файл> <слово>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, argv[2])) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
