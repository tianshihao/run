// Interview Question: What is wrong with this code?
// Key point: std::vector::reserve() only allocates memory but does not create
// elements. Accessing frames_->front() is undefined behavior if the vector is
// empty. This can cause undefined results or runtime errors when using the
// Frame or its members.
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

class Frame {
 public:
  std::unordered_map<int, int> object;
};

class Tracker {
 public:
  void Init() {
    frames_ = std::make_shared<std::vector<Frame>>();
    frames_->reserve(frames_num);

    std::cout << frames_->front().object.size() << std::endl;
    std::cout << "Init done\n";
  }
  void Process() { frames_->front().object.insert({1, 2}); }

 private:
  int frames_num{10};
  std::shared_ptr<std::vector<Frame>> frames_;
};

int main() {
  Tracker tracker;
  tracker.Init();
  tracker.Process();
  tracker.Process();

  return 0;
}
