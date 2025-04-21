#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Розмір сторінки: %ld байт\n", page_size);

    // Виділити одну сторінку пам’яті з правами читання та запису
    void *mem = mmap(NULL, page_size,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("Виділена пам’ять за адресою: %p\n", mem);

    strcpy((char *)mem, "Привіт із захищеної пам’яті!");
    printf("До зміни прав доступу: %s\n", (char *)mem);


    if (mprotect(mem, page_size, PROT_READ) != 0) {
        perror("mprotect");
        munmap(mem, page_size);
        return 1;
    }

    printf("Права доступу змінено на тільки читання\n");

    printf("Спроба запису у пам’ять після mprotect...\n");
    strcpy((char *)mem, "Цей запис має впасти");  // Тут програма падає

    munmap(mem, page_size);
    return 0;
}