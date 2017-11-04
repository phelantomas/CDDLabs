// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Version: 
// Package-Requires: ()
// Last-Updated: Sat Nov  4 17:06:51 2017 (+0000)
//           By: Tomas Phelan
//     Update #: 3
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:

#include "Semaphore.h"
#include <iostream>
#include <thread>

void task(std::shared_ptr<Semaphore> theMutex, std::shared_ptr<Semaphore> turnstile,  std::shared_ptr<Semaphore> turnstile2, int *count, int N){
  /*! allow only one task to increment count */
  theMutex->Wait();
  ++*count;
  if(*count == N){
    turnstile2->Wait();
    turnstile->Signal();
    std::cout << "Count is now " << *count << " equal to N so now allowed through first turnstile \n";
  }
  else{
     std::cout << "Count is now " << *count << " not equal to N so not allowed through first turnstile \n";
  }
  theMutex->Signal();
  
  /*! Only allow througn when count is equal to N */
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
  else{
     std::cout << "Count is now " << *count << " not 0, so not allowed through the second turnstile \n";
  }
  theMutex->Signal();

  /*! Will only allow to go through once all threads catch up */
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
  /*! Launch the threads  */
  threadOne=std::thread(task, mutex, turnstile, turnstile2, &count, N);
  threadTwo=std::thread(task,mutex, turnstile, turnstile2, &count, N);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();

  std::cout << count << std::endl;
  return 0;
}
