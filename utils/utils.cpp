#include "utils.h"

namespace utils {
int PrintUsage() {
  std::cout << "Usage: example [command] [subcommand]\n"
               "\n"
               "Run specified example.\n"
               "\n"
               "Command:\n"
               "    calculate [add|average|complex(default)]\n"
               "    config\n"
               "    loop [loop1|loop2(default)]\n"
               "    performance\n"
               "    reschedule\n"
               "    json_config\n"
               "    flusher\n"
               "    group\n"
               "    help \n"
               "\n"
               "Extra:\n"
               " \n"
               "You can use tools such as valgrind to check memory leaks\n"
               "valgrind --leak-check=full"
               " --show-leak-kinds=all example [command] [subcommand]  "
            << std::endl;

  return 0;
}
}  // namespace utils
