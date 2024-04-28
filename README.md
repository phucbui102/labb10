#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex; // Khai báo biến mutex
int counter = 0; // Biến đếm

// Hàm cho thread 1
void* thread1_function(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex); // Khóa mutex trước khi thay đổi biến
        counter++; // Tăng biến lên 1 đơn vị
        pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi hoàn thành thay đổi
    }
    return NULL;
}

// Hàm cho thread 2
void* thread2_function(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex); // Khóa mutex trước khi thay đổi biến
        counter++; // Tăng biến lên 1 đơn vị
        pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi hoàn thành thay đổi
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

pthread_mutex_init(&mutex, NULL); // Khởi tạo mutex

// Tạo các thread
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

// Chờ các thread kết thúc
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

pthread_mutex_destroy(&mutex); // Hủy mutex

printf("Giá trị của biến counter: %d\n", counter);

return 0;
}
