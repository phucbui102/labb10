#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void printOddDivisors(int n) {
    printf("Tiến trình cha (PID: %d): Các ước số lẻ của %d: ", getpid(), n);
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i % 2 != 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void printEvenDivisors(int n) {
    printf("Tiến trình con (PID: %d): Các ước số chẵn của %d: ", getpid(), n);
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i % 2 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Sử dụng: %s <số_nguyên_dương_n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

  int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Số nguyên dương n không hợp lệ\n");
        exit(EXIT_FAILURE);
    }

  pid_t pid = fork();

  if (pid < 0) {
        // fork() thất bại
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Trong tiến trình con
        printEvenDivisors(n);
        exit(EXIT_SUCCESS);
    } else {
        // Trong tiến trình cha
        printOddDivisors(n);
   // Chờ tiến trình con kết thúc
    wait(NULL);
   }

return 0;
}
