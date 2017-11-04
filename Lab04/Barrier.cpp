// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Version: 
// Package-Requires: ()
// Last-Updated: Sat Nov  4 17:05:28 2017 (+0000)
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
