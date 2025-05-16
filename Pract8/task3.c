#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция сравнения для qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Генерация наихудшего случая (уже отсортированный массив)
void generate_worst_case(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

// Генерация случайного массива
void generate_random_case(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
}

// Тестирование qsort
void test_qsort(int *arr, int size, const char *case_name) {
    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s case: %f seconds\n", case_name, time_spent);
}

int main() {
    const int size = 100000;
    int *arr = malloc(size * sizeof(int));
    
    // Тест 1: Наихудший случай (отсортированный массив)
    generate_worst_case(arr, size);
    test_qsort(arr, size, "Worst");
    
    // Тест 2: Случайный массив
    generate_random_case(arr, size);
    test_qsort(arr, size, "Random");
    
    // Тест 3: Почти отсортированный массив
    generate_worst_case(arr, size);
    // Добавляем немного случайности
    for (int i = 0; i < size/100; i++) {
        int idx = rand() % size;
        arr[idx] = rand() % 1000;
    }
    test_qsort(arr, size, "Almost sorted");
    
    free(arr);
    return 0;
}