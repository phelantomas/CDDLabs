/*!
Author: Tomas Phelan
Date: 17/10/17
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>

void taskOne(std::shared_ptr<Semaphore> theSemaphore, int *count){
  /*! Only allows one task in at a time */
  theSemaphore->Wait();
  std::cout << "In critical section of task 1\n";
  std::cout << "Count is now " << *count << " before being incremented\n";
  ++*count;
  std::cout << "Count is now " << *count << " after being incremented\n";
  theSemaphore->Signal();
}
void taskTwo(std::shared_ptr<Semaphore> theSemaphore, int *count){
  theSemaphore->Wait();
  std::cout << "In critical section of task 2\n";
  std::cout << "Count is now " << *count << " before being incremented\n";
  ++*count;
  std::cout << "Count is now " << *count << " after being incremented\n";
  theSemaphore->Signal();
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> mutex(new Semaphore(1));
  int count = 0;
  /*! Launch the threads  */
  std::cout << "Increment Count from 0 to 2 " << "\n";
  threadOne=std::thread(taskTwo, mutex, &count);
  threadTwo=std::thread(taskOne,mutex, &count);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();

  std::cout << count << std::endl;
  return 0;
}
