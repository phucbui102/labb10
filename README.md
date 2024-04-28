#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBER 20

// Hàm in các số chẵn
void* print_even(void* arg) {
    for (int i = 2; i <= MAX_NUMBER; i += 2) {
        printf("Thread 1 - Even: %d\n", i);
    }
    return NULL;
}

// Hàm in các số lẻ
void* print_odd(void* arg) {
    for (int i = 1; i <= MAX_NUMBER; i += 2) {
        printf("Thread 2 - Odd: %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

// Tạo thread cho các công việc
    pthread_create(&thread1, NULL, print_even, NULL);
    pthread_create(&thread2, NULL, print_odd, NULL);

// Chờ các thread kết thúc
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

 return 0;
}
