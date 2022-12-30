#pragma once
#include <cstddef>
#include <sstream>


// Todo: Add glog
// #include "log.h"

#define DECLARE_CLASS_SINGLETON(classname) \
 public:                                   \
  static classname* instance() {           \
    static classname instance;             \
    return &instance;                      \
  };                                       \
                                           \
 private:                                  \
  classname();

// quit if condition is met
#define QUIT_IF(CONDITION, RET, LEVEL, MSG, ...) \
  do {                                           \
    if (CONDITION) {                             \
      L##LEVEL(MSG, ##__VA_ARGS__);              \
      return RET;                                \
    }                                            \
  } while (0);

#define QUIT_IF_VOID_QUIET(CONDITION) \
  do {                                \
    if (CONDITION) {                  \
      return;                         \
    }                                 \
  } while (0);

#define QUIT_IF_VOID(CONDITION, LEVEL, MSG, ...) \
  do {                                           \
    if (CONDITION) {                             \
      L##LEVEL(MSG, ##__VA_ARGS__);              \
      return;                                    \
    }                                            \
  } while (0);

// CUDA foo must use this macro to invoke
#define CUDA_SAFE_CALL(call)                                              \
  do {                                                                    \
    cudaError_t err = call;                                               \
    if (cudaSuccess != err) {                                             \
      LERROR("Cuda error in file %s in line %d : %s", __FILE__, __LINE__, \
             cudaGetErrorString(err));                                    \
      CHECK(false);                                                       \
    }                                                                     \
  } while (0)

#define DISALLOW_COPY_AND_ASSIGN(T) \
 private:                           \
  T(const T&);                      \
  T& operator=(const T&);

#define QUIT_IF_NO_GPU_AVAILABLE                               \
  do {                                                         \
    int cnt = 0;                                               \
    if (cudaGetDeviceCount(&cnt) != cudaSuccess || cnt == 0) { \
      LWARN("No GPU Avaliable yet");                           \
      return 0;                                                \
    }                                                          \
  } while (0)