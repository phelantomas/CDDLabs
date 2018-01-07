#include "Semaphore.h"
#include <iostream>
#include <queue>
#include <memory>

class SafeBuffer{

private:
  std::queue<char> buffer;
  std::shared_ptr<Semaphore> lock;
  std::shared_ptr<Semaphore> occupied;
  std::shared_ptr<Semaphore> available;
  int buffer_size;

public:
  SafeBuffer();
  SafeBuffer(int size);
  int size();
  void enqueue(char c);
  char dequeue();
};
