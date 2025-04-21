#include <stdio.h>

void func_return() {
    asm("addq $8, %rsp");
}

void func() {
    printf ("Всередині функції ()\n");
    func_return();
}

int main() {
    func();
    return 0;
}