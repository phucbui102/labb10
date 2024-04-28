#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_TIRE 4

sem_t chassis_semaphore; // Semaphore cho khung xe
sem_t tire_semaphore;    // Semaphore cho bánh xe

// Hàm sản xuất khung xe
void Produce_chassis() {
    printf("Producing chassis...\n");
}

// Hàm sản xuất bánh xe
void Produce_tire() {
    printf("Producing tire...\n");
}

// Hàm lắp ráp bánh xe vào khung xe
void Put_4_tires_to_chassis() {
    printf("Assembling tires to chassis...\n");
}

// Thread cho bộ phận sản xuất khung xe
void* makeChassis(void* arg) {
    while (1) {
        sem_wait(&chassis_semaphore); // Đợi có sẵn một khung xe trống
        Produce_chassis(); // Sản xuất khung xe
        for (int i = 0; i < NUM_TIRE; ++i) {
            sem_post(&tire_semaphore); // Báo hiệu rằng có sẵn một bánh xe để lắp vào khung xe mới
        }
    }
    return NULL;
}

// Thread cho bộ phận sản xuất bánh xe
void* makeTire(void* arg) {
    while (1) {
        Produce_tire(); // Sản xuất bánh xe
        sem_wait(&tire_semaphore); // Đợi có sẵn một bánh xe để lắp vào khung xe
    }
    return NULL;
}

// Thread cho bộ phận lắp ráp
void* assemble(void* arg) {
    while (1) {
        Put_4_tires_to_chassis(); // Lắp ráp bánh xe vào khung xe
        sem_post(&chassis_semaphore); // Báo hiệu rằng một khung xe đã được lắp ráp xong, cho phép sản xuất khung xe mới
    }
    return NULL;
}

int main() {
    pthread_t thread_chassis, thread_tire, thread_assemble;

// Khởi tạo semaphore
    sem_init(&chassis_semaphore, 0, 1); // Ban đầu có một khung xe trống
    sem_init(&tire_semaphore, 0, 0);    // Ban đầu không có bánh xe nào

 // Tạo các thread cho các bộ phận sản xuất khung xe, sản xuất bánh xe và lắp ráp
    pthread_create(&thread_chassis, NULL, makeChassis, NULL);
    pthread_create(&thread_tire, NULL, makeTire, NULL);
    pthread_create(&thread_assemble, NULL, assemble, NULL);

// Chờ các thread kết thúc (Điều này không xảy ra trong thực tế, ở đây chỉ là để biểu diễn)
    pthread_join(thread_chassis, NULL);
    pthread_join(thread_tire, NULL);
    pthread_join(thread_assemble, NULL);

// Hủy semaphore
    sem_destroy(&chassis_semaphore);
    sem_destroy(&tire_semaphore);

 return 0;
}
