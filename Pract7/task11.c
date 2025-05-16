#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_NAME_LEN 32
#define DATA_OFFSET 4096
#define DISK_SIZE 1048576
#define DISK_NAME "virtual_disk.bin"

typedef struct {
    char name[MAX_NAME_LEN];
    int offset;
    int size;
    int used;
} FileEntry;

FileEntry table[MAX_FILES];

void load_table(FILE *disk) {
    fseek(disk, 0, SEEK_SET);
    fread(table, sizeof(FileEntry), MAX_FILES, disk);
}

void save_table(FILE *disk) {
    fseek(disk, 0, SEEK_SET);
    fwrite(table, sizeof(FileEntry), MAX_FILES, disk);
}

void init_disk() {
    FILE *disk = fopen(DISK_NAME, "wb");
    if (!disk) { perror("fopen"); exit(1); }

    memset(table, 0, sizeof(table));
    fwrite(table, sizeof(FileEntry), MAX_FILES, disk);

    char zero = 0;
    for (int i = DATA_OFFSET; i < DISK_SIZE; i++)
        fwrite(&zero, 1, 1, disk);

    fclose(disk);
    printf("Disk initialized.\n");
}

void create_file(const char *name, const char *content) {
    FILE *disk = fopen(DISK_NAME, "rb+");
    if (!disk) { perror("fopen"); return; }

    load_table(disk);

    for (int i = 0; i < MAX_FILES; i++) {
        if (table[i].used && strcmp(table[i].name, name) == 0) {
            printf("File already exists.\n");
            fclose(disk);
            return;
        }
    }

    int slot = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (!table[i].used) {
            slot = i;
            break;
        }
    }

    if (slot == -1) {
        printf("No space in file table.\n");
        fclose(disk);
        return;
    }

    int offset = DATA_OFFSET;
    for (int i = 0; i < MAX_FILES; i++) {
        if (table[i].used) {
            int end = table[i].offset + table[i].size;
            if (end > offset)
                offset = end;
        }
    }

    int size = strlen(content);
    if (offset + size > DISK_SIZE) {
        printf("Not enough space on disk.\n");
        fclose(disk);
        return;
    }

    strcpy(table[slot].name, name);
    table[slot].offset = offset;
    table[slot].size = size;
    table[slot].used = 1;

    fseek(disk, offset, SEEK_SET);
    fwrite(content, 1, size, disk);

    save_table(disk);
    fclose(disk);

    printf("File '%s' created.\n", name);
}

void read_file(const char *name) {
    FILE *disk = fopen(DISK_NAME, "rb");
    if (!disk) { perror("fopen"); return; }

    load_table(disk);

    for (int i = 0; i < MAX_FILES; i++) {
        if (table[i].used && strcmp(table[i].name, name) == 0) {
            char *buffer = malloc(table[i].size + 1);
            fseek(disk, table[i].offset, SEEK_SET);
            fread(buffer, 1, table[i].size, disk);
            buffer[table[i].size] = '\0';
            printf("Content of '%s':\n%s\n", name, buffer);
            free(buffer);
            fclose(disk);
            return;
        }
    }

    printf("File not found.\n");
    fclose(disk);
}

void delete_file(const char *name) {
    FILE *disk = fopen(DISK_NAME, "rb+");
    if (!disk) { perror("fopen"); return; }

    load_table(disk);

    for (int i = 0; i < MAX_FILES; i++) {
        if (table[i].used && strcmp(table[i].name, name) == 0) {
            table[i].used = 0;
            save_table(disk);
            fclose(disk);
            printf("File '%s' deleted.\n", name);
            return;
        }
    }

    printf("File not found.\n");
    fclose(disk);
}

int main() {
    // Приклад використання
    init_disk();
    create_file("hello.txt", "Hello, world!");
    read_file("hello.txt");
    delete_file("hello.txt");
    read_file("hello.txt"); // Перевірка
    return 0;
}
