#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    
    printf("%d\n", pid);
    return 0;
}