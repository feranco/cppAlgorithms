#include "queue.h"

//common to base abstract class
void MyQueue::error(const char* err) const {
  std::cout << err << std::endl;
}

std::ostream& operator<<(std::ostream& out, const MyQueue& fifo) {
  fifo.dump(out);
  return out;
}
