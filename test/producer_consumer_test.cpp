#include "ex/producer_consumer.hpp"

#include <gtest/gtest.h>

#include <thread>

void ThreadProducer(Producer producer) {
  int product_number{10};
  while (product_number--) {
    producer.ProduceOne();
  }
}

TEST(ProducerConsumerTest, Main) {
  Producer producer_a;
  producer_a.Init(ProducerType::A);
  producer_a.ProduceOne();

  Producer producer_b;
  producer_b.Init(ProducerType::B);
  producer_b.ProduceOne();

  std::thread t1(&ThreadProducer, producer_a);
  std::thread t2(&ThreadProducer, producer_b);
}
