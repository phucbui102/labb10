#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void createChildProcesses(int n) {
    int i;
    pid_t pid;

    for (i = 0; i < n; i++) {
        pid = fork(); // Tạo một tiến trình con mới

        if (pid < 0) {
            // fork() thất bại
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Trong tiến trình con
            printf("Child process PID: %d\n", getpid());
            exit(EXIT_SUCCESS); // Kết thúc tiến trình con
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Sử dụng: %s <số_lượng_tiến_trình>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Số lượng tiến trình phải lớn hơn 0\n");
        exit(EXIT_FAILURE);
    }

    createChildProcesses(n);

    return 0;
}
