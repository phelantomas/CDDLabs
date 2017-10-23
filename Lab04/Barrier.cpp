/*!
Author: Tomas Phelan
Date: 10/10/2017
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>

void task(std::shared_ptr<Semaphore> theSemaphore, std::shared_ptr<Semaphore> theBarrier, int *count, int N){
  theSemaphore->Wait();
  ++*count;
  if(*count == N){
    /*! Allow through the barrier */
    std::cout << "Count is now " << *count << " equal to N" << "\n";
    theBarrier->Signal();
  }
  theSemaphore->Signal();
  theBarrier->Wait();
  theBarrier->Signal();
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> mutex(new Semaphore(1));
  std::shared_ptr<Semaphore> barrier(new Semaphore);
  int count = 0;
  int N = 2;
  /*! Launch the threads  */
  threadOne=std::thread(task, mutex, barrier, &count, N);
  threadTwo=std::thread(task, mutex, barrier, &count, N);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();

  std::cout << count << std::endl;
  return 0;
}
