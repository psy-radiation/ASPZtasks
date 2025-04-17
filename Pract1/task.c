#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 100

int char_to_val(char c) {
    if (isdigit(c)) return c - '0';
    if (isalpha(c)) return toupper(c) - 'A' + 10;
    return -1;
}

int is_valid_char(char c, int base) {
    int val = char_to_val(c);
    return val >= 0 && val < base;
}

int main() {
    int base;
    char input[MAX_LEN];

    if (scanf("%d %s", &base, input) != 2) {
        printf("Невірний ввід\n");
        return 1;
    }

    if (base < 2 || base > 36) {
        printf("Основа повинна бути від 2 до 36\n");
        return 1;
    }

    double result = 0.0;
    double power = 1.0 / base;
    int is_fraction = 0;
    int dot_seen = 0;

    for (int i = 0; input[i] != '\0'; ++i) {
        char c = input[i];

        if (c == '.') {
            if (dot_seen) continue;  // ігнорувати другу крапку
            dot_seen = 1;
            is_fraction = 1;
            continue;
        }

        if (!is_valid_char(c, base)) {
            continue; // ігноруємо недопустимі символи
        }

        int val = char_to_val(c);

        if (!is_fraction) {
            result = result * base + val;
        } else {
            result += val * power;
            power /= base;
        }
    }
    if(is_fraction){
    printf("%lf\n", result);
    } else {
        printf("%.0lf\n", result);
    }
    return 0;
}