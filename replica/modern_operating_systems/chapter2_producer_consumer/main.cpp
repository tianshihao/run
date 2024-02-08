#include <pthread.h>
#include <stdio.h>

#define MAX 1000

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

void *Producer([[maybe_unused]] void *ptr) {
  for (int i = 0; i < MAX; ++i) {
    // Try to acquire lock, or the producer will be blocked.
    pthread_mutex_lock(&the_mutex);
    // Enter critical zone.

    // Check if buffer is ready to store the product.
    while (buffer != 0) {
      // If not, block and wait on condp.
      pthread_cond_wait(&condp, &the_mutex);
    }

    // Producing.
    printf("producing product %d.\n", i);
    buffer = i;

    // Tell consumer is ready to consume.
    pthread_cond_signal(&condc);
    // Leaving critical zone.
    pthread_mutex_unlock(&the_mutex);
  }

  printf("production finished.\n");

  pthread_exit(0);
}

void *Consumer([[maybe_unused]] void *ptr) {
  for (int i = 0; i < MAX; ++i) {
    // Try to acquire lock, or the consumer will be blocked.
    pthread_mutex_lock(&the_mutex);
    // Enter critical zone.

    // Check if there have product to consume.
    while (buffer == 0) {
      // If not, block and wait on condc;
      pthread_cond_wait(&condc, &the_mutex);
    }

    // Consuming.
    printf("consuming product %d\n", buffer);
    buffer = 0;

    // Inform the producer.
    pthread_cond_signal(&condp);

    // Leaving critical zone.
    pthread_mutex_unlock(&the_mutex);
  }

  printf("consumption finished.\n");

  pthread_exit(0);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  pthread_mutex_init(&the_mutex, 0);

  pthread_cond_init(&condc, 0);
  pthread_cond_init(&condp, 0);

  pthread_t producer, consumer;
  pthread_create(&producer, 0, Producer, 0);
  pthread_create(&consumer, 0, Consumer, 0);

  pthread_join(producer, 0);
  pthread_join(consumer, 0);

  pthread_cond_destroy(&condc);
  pthread_cond_destroy(&condp);

  pthread_mutex_destroy(&the_mutex);

  return 0;
}