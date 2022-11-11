#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "factory_method.hpp"
#include "replica/cpp-concurrency-in-action/chapter4/threadsafe_queue.hpp"

struct Storage {
  ThreadsafeQueue<std::shared_ptr<Product>> _queuec;
};

enum class ProducerType { A, B };


class Producer {
 public:
  Producer() noexcept = default;

  void Init(ProducerType type, std::shared_ptr<Storage> storage) {
    switch (type) {
      case ProducerType::A: {
        _factory.reset(new FactoryA());
        break;
      }
      case ProducerType::B: {
        _factory.reset(new FactoryB());
        break;
      }
      default: {
        _factory.reset(new FactoryA());
        break;
      }
    }

    _storage = storage;

    return;
  }

  void ProduceOne() {
    auto product{_factory->Produce()};
    _storage->_queue.Push(std::move(product));

    return;
  }

 private:
  std::unique_ptr<Factory> _factory{nullptr};
  std::shared_ptr<Storage> _storage{nullptr};
};

class Consumer {
 public:
  Consumer() noexcept = default;

 private:
  std::shared_ptr<Product> _product { nullptr }
};
