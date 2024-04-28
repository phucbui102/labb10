#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* ruttien(void* arg)
{

printf("\nRut tien\n");

sleep(2);

printf("\nGhi nhan so du trong tai khoan\n");

4}

int main()

{

pthread_t t1, t2;

pthread_create(&t1, NULL, ruttien, NULL);
pthread_create(&t2, NULL, ruttien, NULL);

pthread_join(t1, NULL);

pthread_join(t2,NULL);
return 0;
}
