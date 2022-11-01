#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "example.h"
#include "utils.h"

static std::map<std::string, fn> examples{
    {"blob", TestBlob}, {"blobptr", TestBlobPtr}, {"screen", TestScreen}};

int main(int argc, char **argv) {
  if (2 > argc || 0 == *argv[1]) {
    utils::PrintUsage();
  } else {
    examples[argv[1]](argc - 1, argv + 1);
  }
  return 0;
}