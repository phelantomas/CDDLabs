//Author: Tomas Phelan
//Date: 10/10/2017
//

#include "Semaphore.h"
#include <iostream>
#include <thread>

void task(std::shared_ptr<Semaphore> theMutex, std::shared_ptr<Semaphore> turnstile,  std::shared_ptr<Semaphore> turnstile2, int *count, int N){
  //allow only one task to increment count
  theMutex->Wait();
  ++*count;
  if(*count == N){
    turnstile2->Wait();
    turnstile->Signal();
    std::cout << "Count is now " << *count << "equal to N so now allowed through first turnstile \n";
  }
  theMutex->Signal();
  
  //Only allow througn when count is equal to N
  turnstile->Wait();
  turnstile->Signal();

  std::cout << "Here is the critical section" << "\n";
  //critical stuff here
  theMutex->Wait();

  --*count;
  if(*count == 0){
    turnstile->Wait();
    turnstile2->Signal();
    std::cout << "Count is now " << *count << " so now allowed through second turnstile \n";    
  }
  theMutex->Signal();

  //Will only allow to go through once all threads catch up
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
