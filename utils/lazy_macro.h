/**
 * @file lazy_macro.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-11-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#define DECLARE_CLASS_SINGLETON(classname) \
 public:                                   \
  static classname *Instance() {           \
    static classname instance;             \
    return &instance;                      \
  };                                       \
                                           \
 private:                                  \
  classname();

#define DECLARE_CLASS_COPY_DEFAULT(classname)      \
 public:                                           \
  classname(classname const &) noexcept = default; \
  classname &operator=(classname const &) noexcept = default;

#define DECLARE_CLASS_COPY_DELETE(classname)  \
 public:                                 \
  classname(classname const &) = delete; \
  classname &operator=(classname const &) = delete;

#define DECLARE_CLASS_MOVE_DEFAULT(classname) \
  classname(classname &&) noexcept = default; \
  classname &operator=(classname &&) noexcept = default;

#define DECLARE_CLASS_MOVE_DELETE(classname) \
  classname(classname &&) = delete;          \
  classname &operator=(classname &&) = delete;
