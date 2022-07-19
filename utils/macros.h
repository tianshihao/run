#pragma once

namespace run::utils {

#define DECLARE_CLASS_SINGLETON(classname)          \
 public:                                            \
  static classname &Instance() {                    \
    static classname instance;                      \
    return instance;                                \
  }                                                 \
                                                    \
  classname(const classname &) = delete;            \
  classname &operator=(const classname &) = delete; \
                                                    \
 private:                                           \
  classname() = default;                            \
  ~classname() = default;

// quit if cond is met
#define QUIT_IF(cond, ret, level, ...) \
  do {                                 \
    if (UNLIKELY(cond)) {              \
      LOG_##level(__VA_ARGS__);        \
      return ret;                      \
    }                                  \
  } while (false)

#define QUIT_IF_VOID(cond, level, ...) \
  do {                                 \
    if (UNLIKELY(cond)) {              \
      LOG_##level(__VA_ARGS__);        \
      return;                          \
    }                                  \
  } while (false)

#define QUIT_IF_VOID_QUIET(cond) \
  do {                           \
    if (UNLIKELY(cond)) {        \
      return;                    \
    }                            \
  } while (false)

#define DISALLOW_COPY_AND_ASSIGN(T) \
 private:                           \
  T(const T &);                     \
  T &operator=(const T &);

}  // namespace run::utils
