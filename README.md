#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

pthread_mutex_t mutex; // Khai báo biến mutex
int x[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Mảng số nguyên
int sumB = 0, sumC = 0, sumD = 0; // Biến tổng

// Hàm tính tổng các số chẵn trong mảng x
void* calculate_even_sum(void* arg) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (x[i] % 2 == 0) {
            pthread_mutex_lock(&mutex); // Khóa mutex trước khi thay đổi biến sumB
            sumB += x[i];
            pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi hoàn thành thay đổi
        }
    }
    return NULL;
}

// Hàm tính tổng các số lẻ trong mảng x
void* calculate_odd_sum(void* arg) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (x[i] % 2 != 0) {
            pthread_mutex_lock(&mutex); // Khóa mutex trước khi thay đổi biến sumC
            sumC += x[i];
            pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi hoàn thành thay đổi
        }
    }
    return NULL;
}

// Hàm tính tổng sumD dựa trên sumB và sumC
void* calculate_total_sum(void* arg) {
    pthread_mutex_lock(&mutex); // Khóa mutex trước khi tính toán sumD
    sumD = sumB + sumC;
    pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi hoàn thành tính toán
    return NULL;
}

int main() {
    pthread_t threadB, threadC, threadD;

pthread_mutex_init(&mutex, NULL); // Khởi tạo mutex

 // Tạo các thread cho các công việc
    pthread_create(&threadB, NULL, calculate_even_sum, NULL);
    pthread_create(&threadC, NULL, calculate_odd_sum, NULL);

// Chờ các thread B và C kết thúc
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

// Tạo thread D để tính tổng sumD
    pthread_create(&threadD, NULL, calculate_total_sum, NULL);

// Chờ thread D kết thúc
    pthread_join(threadD, NULL);

pthread_mutex_destroy(&mutex); // Hủy mutex

// In ra kết quả
    printf("Tong cac so chan trong mang: %d\n", sumB);
    printf("Tong cac so le trong mang: %d\n", sumC);
    printf("Tong cac phan tu trong mang: %d\n", sumD);

 return 0;
}
