#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int depth = 0;
    pid_t pid;

    while (depth < 5) {
        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Це дочірній процес
            depth++;
            printf("Child process at depth %d, PID = %d, PPID = %d\n", depth, getpid(), getppid());
        } else {
            // Це батьківський процес: чекає на свою дитину і виходить
            wait(NULL);
            break;
        }
    }

    return 0;
}
