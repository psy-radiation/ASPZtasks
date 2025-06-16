#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define INTERVALS_COUNT 5
int intervals[INTERVALS_COUNT] = {1, 5, 10, 30, 60};

volatile sig_atomic_t ticked = 0;
struct timespec start_time, end_time;

void handler(int sig, siginfo_t *si, void *uc) {
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    ticked = 1;
}

double timespec_diff(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) + 
           (end->tv_nsec - start->tv_nsec) / 1e9;
}

int main() {
    struct sigaction sa = {0};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigaction(SIGRTMIN, &sa, NULL);

    for (int i = 0; i < INTERVALS_COUNT; ++i) {
        int seconds = intervals[i];
        printf("Testing %d-second timer...\n", seconds);

        ticked = 0;
        timer_t timerid;
        struct sigevent sev = {0};
        sev.sigev_notify = SIGEV_SIGNAL;
        sev.sigev_signo = SIGRTMIN;

        timer_create(CLOCK_REALTIME, &sev, &timerid);

        struct itimerspec its = {0};
        its.it_value.tv_sec = seconds;
        its.it_value.tv_nsec = 0;

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        timer_settime(timerid, 0, &its, NULL);

        while (!ticked) pause();

        double elapsed = timespec_diff(&start_time, &end_time);
        printf("Expected: %d.000s, Actual: %.3fs, Delta: %.3fs\n\n",
               seconds, elapsed, elapsed - seconds);

        timer_delete(timerid);
    }

    return 0;
}
