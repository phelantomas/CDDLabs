// Mutex.cpp --- 
// 
// Filename: Mutex.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Version: 
// Package-Requires: ()
// Last-Updated: Sat Nov  4 17:03:48 2017 (+0000)
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
