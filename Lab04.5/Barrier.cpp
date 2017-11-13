// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Version: 
// Package-Requires: ()
// Last-Updated: Tue Nov  7 15:53:00 2017 (+0000)
//           By: Tomas Phelan
//     Update #: 11
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
#include <mutex>

void Barrier::FirstTurnstile(){
  	mutex->Wait();
	++count;
	if(count == numberOfThreads){
	  turnstileB->Wait();
	  turnstileA->Signal();
	}
	mutex->Signal();
        turnstileA->Wait();
	turnstileA->Signal();
}

void Barrier::SecondTurnstile(){	
	mutex->Wait();
	--count;
	if(count == 0){
	  turnstileA->Wait();
	  turnstileB->Signal();
	}
	mutex->Signal();
	turnstileB->Wait();
	turnstileB->Signal();
}

void Barrier::Wait(){
  	FirstTurnstile();
  	SecondTurnstile();
}

Barrier::Barrier(int count){
	  numberOfThreads = count;
	  this->count = 0;
	  mutex=std::make_shared<Semaphore>(1);
	  turnstileA=std::make_shared<Semaphore>(0);
	  turnstileB=std::make_shared<Semaphore>(1);
}

