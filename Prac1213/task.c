#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>

int temp_fd = -1;
int sock_fd = -1;

// Простий write wrapper для безпечного виводу
void log_message(const char *msg) {
    write(STDERR_FILENO, msg, strlen(msg));
}

void safe_exit(int sig) {
    log_message("\n[!] Signal received: cleaning up resources...\n");

    if (sock_fd != -1) {
        close(sock_fd);
        log_message("[+] Socket closed.\n");
    }

    if (temp_fd != -1) {
        close(temp_fd);
        unlink("/tmp/tempfile");
        log_message("[+] Temp file closed and unlinked.\n");
    }

    log_message("[*] Exiting safely.\n");
    _exit(1);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = safe_exit;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    temp_fd = open("/tmp/tempfile", O_CREAT | O_WRONLY, 0600);

    if (sock_fd == -1 || temp_fd == -1) {
        perror("resource allocation failed");
        exit(1);
    }

    printf("[*] Program running (PID: %d)...\n", getpid());
    printf("[*] Resources allocated: socket=%d, temp_fd=%d\n", sock_fd, temp_fd);
    printf("[*] Press Ctrl+C or send SIGTERM to test cleanup.\n");

    while (1) {
        pause();
    }

    return 0;
}
