#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t chassis_semaphore; // Semaphore cho khung xe
sem_t tire_semaphore;    // Semaphore cho bánh xe

// Bộ phận sản xuất khung xe
void Produce_chassis() {
    // Sản xuất khung xe
    printf("Producing chassis...\n");
    // Giả sử quá trình sản xuất mất một thời gian
    // Đợi một khoảng thời gian ngắn để mô phỏng quá trình sản xuất
    sleep(1);
}

// Bộ phận sản xuất bánh xe
void Produce_tire() {
    // Sản xuất bánh xe
    printf("Producing tire...\n");
    // Giả sử quá trình sản xuất mất một thời gian
    // Đợi một khoảng thời gian ngắn để mô phỏng quá trình sản xuất
    sleep(1);
}

// Bộ phận lắp ráp
void Put_4_tires_to_chassis() {
    // Lắp ráp bánh xe vào khung xe
    printf("Assembling tires to chassis...\n");
    // Giả sử quá trình lắp ráp mất một thời gian
    // Đợi một khoảng thời gian ngắn để mô phỏng quá trình lắp ráp
    sleep(1);
}

// Bộ phận sản xuất khung xe
void* makeChassis(void* arg) {
    while (1) {
        sem_wait(&chassis_semaphore); // Chờ có sẵn một khoảng trống để sản xuất khung xe
        Produce_chassis(); // Sản xuất khung xe
        sem_post(&tire_semaphore); // Báo hiệu rằng một khung xe đã được sản xuất, cho phép sản xuất bánh xe tiếp theo
    }
    return NULL;
}

// Bộ phận sản xuất bánh xe
void* MakeTire(void* arg) {
    while (1) {
        sem_wait(&tire_semaphore); // Chờ có sẵn đủ bánh xe để lắp vào khung xe
        Produce_tire(); // Sản xuất bánh xe
        sem_post(&tire_semaphore); // Báo hiệu rằng một bánh xe đã được sản xuất
        sem_post(&chassis_semaphore); // Báo hiệu rằng một bánh xe đã được sản xuất, cho phép sản xuất khung xe tiếp theo
    }
    return NULL;
}

// Bộ phận lắp ráp
void* Asemble(void* arg) {
    while (1) {
        sem_wait(&tire_semaphore); // Chờ có sẵn đủ bánh xe để lắp vào khung xe
        Put_4_tires_to_chassis(); // Lắp ráp bánh xe vào khung xe
    }
    return NULL;
}

int main() {
    pthread_t thread_chassis, thread_tire, thread_assemble;

// Khởi tạo semaphore
    sem_init(&chassis_semaphore, 0, 1); // Khởi tạo với giá trị ban đầu là 1 (một khung xe có thể được sản xuất ngay lập tức)
    sem_init(&tire_semaphore, 0, 0);    // Khởi tạo với giá trị ban đầu là 0 (không có bánh xe nào có sẵn để lắp vào khung xe)

// Tạo các thread cho các bộ phận sản xuất khung xe, sản xuất bánh xe và lắp ráp
    pthread_create(&thread_chassis, NULL, makeChassis, NULL);
    pthread_create(&thread_tire, NULL, MakeTire, NULL);
    pthread_create(&thread_assemble, NULL, Asemble, NULL);

// Chờ các thread kết thúc (Điều này không xảy ra trong thực tế, ở đây chỉ là để biểu diễn)
    pthread_join(thread_chassis, NULL);
    pthread_join(thread_tire, NULL);
    pthread_join(thread_assemble, NULL);

// Hủy semaphore
    sem_destroy(&chassis_semaphore);
    sem_destroy(&tire_semaphore);

 return 0;
}
