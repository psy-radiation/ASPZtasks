#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    // Максимальне значення знакового типу time_t
    time_t max_time = (time_t)~((time_t)1 << (sizeof(time_t) * 8 - 1));

    printf("Max time_t value: %ld\n", (long)max_time);
    printf("Date and time: %s", ctime(&max_time));

    time_t overflow_time = max_time + 1;
    printf("After overflow: %s", ctime(&overflow_time));

    return 0;
}
