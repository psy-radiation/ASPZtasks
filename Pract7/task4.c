#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[256];
    int count = 0;

    for (int i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            if (++count % 20 == 0) {
                printf("Натисніть Enter для продовження...");
                getchar();
            }
        }
        fclose(file);
    }

    return 0;
}
