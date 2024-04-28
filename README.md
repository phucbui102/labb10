#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t chassis_semaphore;    // Semaphore cho việc sản xuất khung xe
sem_t tire_semaphore;       // Semaphore cho việc sản xuất bánh xe
sem_t assemble_semaphore;   // Semaphore cho việc lắp ráp
int tire_count = 0;         // Đếm số lượng bánh xe đã sản xuất

void Produce_chassis() {
    // Sản xuất khung xe
    printf("Producing chassis...\n");
}

void Produce_tire() {
    // Sản xuất bánh xe
    printf("Producing tire...\n");
    tire_count++;
}

void Put_4_tires_to_chassis() {
    // Lắp 4 bánh xe vào khung xe
    printf("Assembling tires to chassis...\n");
    tire_count -= 4;
}

void *makeChassis(void *arg) {
    while (1) {
        sem_wait(&chassis_semaphore);  // Chờ đến khi được phép sản xuất khung xe
        Produce_chassis();
        sem_post(&tire_semaphore);     // Bắt đầu sản xuất 4 bánh xe sau khi có khung xe
    }
}

void *MakeTire(void *arg) {
    while (1) {
        Produce_tire();
        if (tire_count >= 4) {
            sem_post(&assemble_semaphore);  // Báo hiệu rằng đã có đủ bánh xe để lắp ráp
            sem_post(&assemble_semaphore);
            sem_post(&assemble_semaphore);
            sem_post(&assemble_semaphore);
        }
    }
}

void *assemble(void *arg) {
    while (1) {
        sem_wait(&assemble_semaphore);  // Chờ đến khi có đủ bánh xe để lắp ráp
        sem_wait(&assemble_semaphore);
        sem_wait(&assemble_semaphore);
        sem_wait(&assemble_semaphore);
        Put_4_tires_to_chassis();
        sem_post(&chassis_semaphore);   // Báo hiệu rằng đã lắp ráp xong và có thể sản xuất khung xe tiếp theo
    }
}

int main() {
    pthread_t chassis_thread, tire_thread, assemble_thread;

// Khởi tạo Semaphore
    sem_init(&chassis_semaphore, 0, 1);
    sem_init(&tire_semaphore, 0, 0);
    sem_init(&assemble_semaphore, 0, 0);

// Tạo các luồng
    pthread_create(&chassis_thread, NULL, makeChassis, NULL);
    pthread_create(&tire_thread, NULL, MakeTire, NULL);
    pthread_create(&assemble_thread, NULL, assemble, NULL);

// Chờ các luồng kết thúc (điều này không xảy ra trong trường hợp này)
    pthread_join(chassis_thread, NULL);
    pthread_join(tire_thread, NULL);
    pthread_join(assemble_thread, NULL);

// Hủy Semaphore
    sem_destroy(&chassis_semaphore);
    sem_destroy(&tire_semaphore);
    sem_destroy(&assemble_semaphore);

return 0;
}
