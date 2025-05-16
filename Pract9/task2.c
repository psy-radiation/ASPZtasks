#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Trying to read /etc/shadow as regular user:\n");
    system("cat /etc/shadow 2>&1 | head -n 3");
    
    printf("\nNow trying with sudo:\n");
    system("sudo cat /etc/shadow 2>&1 | head -n 3");
    
    return 0;
}