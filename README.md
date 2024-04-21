#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void createProcesses() {
    pid_t pid_A, pid_B, pid_C, pid_D, pid_E, pid_F, pid_G, pid_H;

    // Tạo tiến trình A
    pid_A = getpid();
    printf("Process A (PID: %d) - Parent PID: %d\n", pid_A, getppid());

    // Tạo tiến trình B từ tiến trình A
    pid_B = fork();
    if (pid_B == 0) {
        // Trong tiến trình con B
        printf("Process B (PID: %d) - Parent PID: %d\n", getpid(), getppid());

        // Tạo tiến trình D từ tiến trình B
        pid_D = fork();
        if (pid_D == 0) {
            // Trong tiến trình con D
            printf("Process D (PID: %d) - Parent PID: %d\n", getpid(), getppid());
        }
    } else {
        // Tạo tiến trình C từ tiến trình A
        pid_C = fork();
        if (pid_C == 0) {
            // Trong tiến trình con C
            printf("Process C (PID: %d) - Parent PID: %d\n", getpid(), getppid());

            // Tạo tiến trình H từ tiến trình C
            pid_H = fork();
            if (pid_H == 0) {
                // Trong tiến trình con H
                printf("Process H (PID: %d) - Parent PID: %d\n", getpid(), getppid());
            }
        }
    }

    // Tạo tiến trình E từ tiến trình B
    if (pid_B == 0) {
        pid_E = fork();
        if (pid_E == 0) {
            // Trong tiến trình con E
            printf("Process E (PID: %d) - Parent PID: %d\n", getpid(), getppid());
        }
    }

    // Tạo tiến trình F từ tiến trình E
    if (pid_E == 0) {
        pid_F = fork();
        if (pid_F == 0) {
            // Trong tiến trình con F
            printf("Process F (PID: %d) - Parent PID: %d\n", getpid(), getppid());
        }
    }

    // Tạo tiến trình G từ tiến trình E
    if (pid_E == 0) {
        pid_G = fork();
        if (pid_G == 0) {
            // Trong tiến trình con G
            printf("Process G (PID: %d) - Parent PID: %d\n", getpid(), getppid());
        }
    }
}

int main() {
    createProcesses();
    return 0;
}
