#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex; // Khai báo biến mutex

int account_balance = 0; // Số dư tài khoản

// Hàm rút tiền
void* ruttien(void* arg) {
    int amount = *((int*)arg); // Lấy giá trị rút từ tham số
    printf("\nRut tien: %d\n", amount);

pthread_mutex_lock(&mutex); // Khóa mutex trước khi thay đổi số dư
    account_balance -= amount; // Rút tiền
    printf("\nSo du sau khi rut tien: %d\n", account_balance);
    pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi hoàn thành thay đổi
    return NULL;
}

// Hàm nạp tiền
void* naptien(void* arg) {
    int amount = *((int*)arg); // Lấy giá trị nạp từ tham số
    printf("\nNap tien: %d\n", amount);

pthread_mutex_lock(&mutex); // Khóa mutex trước khi thay đổi số dư
    account_balance += amount; // Nạp tiền
    printf("\nSo du sau khi nap tien: %d\n", account_balance);
    pthread_mutex_unlock(&mutex); // Mở khóa mutex sau khi hoàn thành thay đổi
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

pthread_mutex_init(&mutex, NULL); // Khởi tạo mutex

int nap_amount = 200; // Số tiền cần nạp
    int rut_amount = 100; // Số tiền cần rút

// Tạo các thread cho các công việc
    pthread_create(&thread1, NULL, ruttien, (void*)&rut_amount);
    pthread_create(&thread2, NULL, naptien, (void*)&nap_amount);

// Chờ các thread kết thúc
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

pthread_mutex_destroy(&mutex); // Hủy mutex khi không cần nữa

return 0;
}
