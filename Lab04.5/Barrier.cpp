//Author: Tomas Phelan
//Date: 10/10/2017
//

#include "Semaphore.h"
#include <iostream>
#include <thread>

void task(std::shared_ptr<Semaphore> theMutex, std::shared_ptr<Semaphore> turnstile,  std::shared_ptr<Semaphore> turnstile2, int *count, int N){
  theMutex->Wait();
  ++*count;
  if(*count == N){
    turnstile2->Wait();
    turnstile->Signal();
  }
  theMutex->Signal();
  
  turnstile->Wait();
  turnstile->Signal();

  //critical stuff here

  theMutex->Wait();

  --*count;
  if(*count == 0){
    turnstile->Wait();
    turnstile2->Signal();
  }
  theMutex->Signal();
  
  turnstile2->Wait();
  turnstile2->Signal();
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> mutex(new Semaphore(1));
  std::shared_ptr<Semaphore> turnstile(new Semaphore);
  std::shared_ptr<Semaphore> turnstile2(new Semaphore(1));
  int count = 0;
  int N = 2;
  /**< Launch the threads  */
  threadOne=std::thread(task, mutex, turnstile, turnstile2, &count, N);
  threadTwo=std::thread(task,mutex, turnstile, turnstile2, &count, N);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();

  std::cout << count << std::endl;
  return 0;
}
