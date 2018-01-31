// main.cpp --- 
// 
// Filename: main.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Sat Nov  4 20:07:20 2017 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Wed Jan 31 12:41:35 2018 (+0000)
//           By: Tomas Phelan
//     Update #: 17
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

#include "Barrier.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <limits>
#include <vector>

/*!
  Task implementing the reuasbale barrier
*/


/*! 
brief: Allows multiple theads in.
parameters: theBarrier, threadId
*/
void task(std::shared_ptr<Barrier> theBarrier, int threadId){
  std::cout << "Thread "<< threadId << " entered the first turnstile" << std::endl;
  theBarrier->FirstTurnstile();
  std::cout << "Thread "<< threadId << " entered the second turnstile" << std::endl;
  theBarrier->SecondTurnstile();
}

int main(void){

  int numberOfThreads = 0;
  std::cout << "Enter in number of threads wanted: ";
 
  while(!(std::cin >> numberOfThreads)){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input.  Try again: ";
  }
  std::cout << "You entered: " << numberOfThreads << std::endl;
	
  std::thread threadArray[numberOfThreads] ;
  std::shared_ptr<Barrier> theBarrier(new Barrier(numberOfThreads));
  

  for(int i = 0; i < numberOfThreads; ++i){
    threadArray[i] = std::thread(task, theBarrier, i);
  }
  
  for(int i = 0; i < numberOfThreads; ++i){
    threadArray[i].join(); 
  }
  
  std::cout << "All threads are now finished"<< std::endl;
  
  return 0;
}




// 
// main.cpp ends here
