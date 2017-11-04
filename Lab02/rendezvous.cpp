// rendezvous.cpp --- 
// 
// Filename: rendezvous.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Wed Oct 25 12:53:19 2017 (+0100)
// Version: 
// Package-Requires: ()
// Last-Updated: Sat Nov  4 17:01:19 2017 (+0000)
//           By: Tomas Phelan
//     Update #: 2
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

void taskOne(std::shared_ptr<Semaphore> taskOneSem,std::shared_ptr<Semaphore> taskTwoSem){
  std::cout << "A1 Prints Before B2 "<<std::endl;
  /*! Will now allow B2 to print */
  taskOneSem->Signal();
  taskTwoSem->Wait();
  std::cout << "A2 Prints After B1 "<<std::endl;
}
void taskTwo(std::shared_ptr<Semaphore> taskOneSem,std::shared_ptr<Semaphore> taskTwoSem){
  std::cout << "B1 Prints Before A2 "<<std::endl;
  taskTwoSem->Signal();
  /*! Will prevent B2 from printing if not A1 has not already printed */
  taskOneSem->Wait();
  std::cout << "B2 Prints After A1 "<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> taskOneSem( new Semaphore);
  std::shared_ptr<Semaphore> taskTwoSem( new Semaphore);
  std::cout << "Task: B1 always print before A2, and A1 always print before B2.\n";
  /*! Launch the threads  */
  threadOne=std::thread(taskOne, taskOneSem, taskTwoSem);
  threadTwo=std::thread(taskTwo, taskOneSem, taskTwoSem);

  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
