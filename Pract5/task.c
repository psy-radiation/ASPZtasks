#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024 * 1024 // 1 МБ
#define MAX_HEAP_MB 10

int main() {
    void* blocks[10];

    // Виділяємо 10 блоків по 1 МБ (всього 10 МБ)
    for (int i = 0; i < MAX_HEAP_MB; i++) {
        blocks[i] = malloc(BLOCK_SIZE);
        if (blocks[i] == NULL) {
            printf("malloc(%d) failed\n", i);
            return 1;
        }
    }

    // Звільняємо непослідовні блоки (фрагментація)
    for (int i = 0; i < MAX_HEAP_MB; i += 2) {
        free(blocks[i]);
    }

    // Спроба виділити 3 МБ — має провалитися
    void* big = malloc(3 * BLOCK_SIZE);
    if (big == NULL) {
        printf("Виділення 3 МБ не вдалося через фрагментацію\n");
    } else {
        printf("Виділено великий блок, фрагментація не спрацювала: %p\n", big);
        free(big);
    }

    // Очищення
    for (int i = 1; i < MAX_HEAP_MB; i += 2) {
        free(blocks[i]);
    }

    return 0;
}
