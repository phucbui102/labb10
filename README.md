#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void createProcess(char parent, char child) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Trong tiến trình con
        printf("Process %c PID: %d\n", child, getpid());
        printf("Parent of Process %c PID: %d\n", child, getppid());
    } else {
        // Trong tiến trình cha
        wait(NULL); // Đợi cho đến khi tiến trình con kết thúc
    }
}

int main() {
    createProcess('A', 'B');
    createProcess('A', 'C');
    createProcess('B', 'E');
    createProcess('B', 'D');
    createProcess('C', 'H');
    createProcess('D', 'I');
    createProcess('D', 'J');
    return 0;
}
