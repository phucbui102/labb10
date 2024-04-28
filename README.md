#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex; // Khai báo mutex

void* ruttien(void* arg)
{
    // Khóa mutex trước khi thực hiện công việc
    pthread_mutex_lock(&mutex);
   printf("\nRut tien\n");
    sleep(2);
    printf("\nGhi nhan so du trong tai khoan\n");

   // Mở khóa mutex sau khi hoàn thành công việc
    pthread_mutex_unlock(&mutex);

  return NULL;
}

int main()
{
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    // Tạo các thread
    pthread_create(&t1, NULL, ruttien, NULL);
    pthread_create(&t2, NULL, ruttien, NULL);
    // Chờ các thread kết thúc
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

   // Hủy mutex
    pthread_mutex_destroy(&mutex);

  return 0;
}
