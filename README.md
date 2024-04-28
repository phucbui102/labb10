#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBER 20

pthread_mutex_t mutex; // Khai báo biến mutex
int counter = 1; // Biến đếm

// Hàm in các số chẵn
void* print_even(void* arg) {
    while (counter <= MAX_NUMBER) {
        pthread_mutex_lock(&mutex); // Khóa mutex trước khi in
        if (counter % 2 == 0) {
            printf("Thread 1 - Even: %d\n", counter);
            counter++; // Tăng biến lên 1 nếu là số chẵn
        }
        pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi in
    }
    return NULL;
}

// Hàm in các số lẻ
void* print_odd(void* arg) {
    while (counter <= MAX_NUMBER) {
        pthread_mutex_lock(&mutex); // Khóa mutex trước khi in
        if (counter % 2 != 0) {
            printf("Thread 2 - Odd: %d\n", counter);
            counter++; // Tăng biến lên 1 nếu là số lẻ
        }
        pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi in
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

 pthread_mutex_init(&mutex, NULL); // Khởi tạo mutex

// Tạo các thread
    pthread_create(&thread1, NULL, print_even, NULL);
    pthread_create(&thread2, NULL, print_odd, NULL);

// Chờ các thread kết thúc
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

pthread_mutex_destroy(&mutex); // Hủy mutex

return 0;
}
