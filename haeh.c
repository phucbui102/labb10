#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void createProcess(char name, int num_children) {
    printf("Process %c PID: %d\n", name, getpid());
    printf("Parent of Process %c PID: %d\n", name, getppid());

    for (int i = 0; i < num_children; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Trong tiến trình con
            createProcess(name + 1, i == 0 ? 2 : 1); // Tạo 2 tiến trình con đầu tiên của B và một tiến trình con của các tiến trình còn lại
            exit(EXIT_SUCCESS);
        } else {
            // Trong tiến trình cha
            wait(NULL); // Đợi cho đến khi tiến trình con kết thúc
        }
    }
}

int main() {
    createProcess('A', 2);
    return 0;
}
