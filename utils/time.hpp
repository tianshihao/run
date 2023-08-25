
#include <chrono>
#include <string>
#include <thread>

namespace run::time {
using Seconds = int64_t;
using Milliseconds = int64_t;
using Microseconds = int64_t;
using Nanoseconds = int64_t;

// /// @brief get after now timestamp in timespec
// /// @param ns after nanoseconds
// /// @return timestamp in timespec
// struct timespec AfterNowTimeSpec(int64_t const ns) noexcept;

// /// @brief get current timestamp in timespec
// /// @return timestamp in timespec
// struct timespec NowTimeSpec() noexcept;

/// @brief convert seconds to nanoseconds
/// @param sec seconds
/// @return nanoseconds
Nanoseconds SecondsToNanoseconds(Nanoseconds const sec) noexcept {
  return sec * 1000000000;
}

/// @brief sleep for milliseconds(ms)
/// @param ms milliseconds(ms) to sleep
void SleepForMilliseconds(Milliseconds const ms) noexcept {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

/// @brief sleep for microseconds(µs)
/// @param us microseconds(µs) to sleep
void SleepForMicroseconds(Microseconds const us) noexcept {
  std::this_thread::sleep_for(std::chrono::microseconds(us));
}

/// @brief get current timestamp in seconds
/// @return timestamp in seconds
Seconds NowSeconds() noexcept {
  return std::chrono::duration_cast<std::chrono::seconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

/// @brief get current timestamp in milliseconds(ms)
/// @return timestamp in milliseconds(ms)
Milliseconds NowMilliseconds() noexcept {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

/// @brief get current timestamp in microseconds(µs)
/// @return timestamp in microseconds(µs)
Microseconds NowMicroseconds() noexcept {
  return std::chrono::duration_cast<std::chrono::microseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

/// @brief get current timestamp in nanoseconds(ns)
/// @return timestamp in nanoseconds(ns)
Nanoseconds NowNanoseconds() noexcept {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

// /// @brief get current time string
// /// @return time string in "hh:mm:ss.ms" format
// std::string FormatTime() noexcept;

// /// @brief get current date-time string
// /// @return date-time string in "yyyy-mm-dd.hh:mm:ss.ms" format
// std::string FormatDateTime() noexcept;

}  // namespace run::time
