#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    printf("0.0 - 1.0: %.6f\n", (float)rand() / RAND_MAX);

    float n;
    printf("Введіть n: ");
    scanf("%f", &n);
    printf("0.0 - %.2f: %.6f\n", n, ((float)rand() / RAND_MAX) * n);

    return 0;
}
