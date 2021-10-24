#include "../csapp.h"

void *thread(void *vargs);

int main(int argc, char **argv) {
  pthread_t tid;
  pthread_create(&tid, NULL, thread, NULL);
  pthread_join(tid, NULL);

  return 0;
}

void *thread(void *vargs) {
  printf("Hello, world!\n");
  return NULL;
}