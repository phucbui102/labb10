#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
double account_balance = 1000.0; // Số dư ban đầu

void* ruttien(void* arg) {
    printf("\nRut tien\n");
    sleep(2);
    
 pthread_mutex_lock(&lock); // Khóa mutex trước khi truy cập vào biến số dư
    printf("\nGhi nhan so du trong tai khoan: %.2f\n", account_balance);
    pthread_mutex_unlock(&lock); // Mở khóa mutex sau khi hoàn thành
    
 pthread_exit(NULL);
}

void* naptien(void* arg) {
    printf("\nNap tien\n");
    sleep(2);
    
 pthread_mutex_lock(&lock); // Khóa mutex trước khi truy cập vào biến số dư
    account_balance += 500.0; // Nạp 500 vào tài khoản
    printf("\nGhi nhan so du trong tai khoan: %.2f\n", account_balance);
    pthread_mutex_unlock(&lock); // Mở khóa mutex sau khi hoàn thành
    
 pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    
 pthread_mutex_init(&lock, NULL); // Khởi tạo mutex
    
// Tạo thread cho rút tiền và nạp tiền
    pthread_create(&thread1, NULL, ruttien, NULL);
    pthread_create(&thread2, NULL, naptien, NULL);
    
 // Chờ các thread kết thúc
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
 pthread_mutex_destroy(&lock); // Hủy mutex
    
 return 0;
}
