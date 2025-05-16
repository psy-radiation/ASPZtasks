#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();

    for (volatile int i = 0; i < 100000000; i++); // Затримка

    clock_t end = clock();
    double time_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    printf("Час виконання: %.2f мс\n", time_ms);

    return 0;
}
