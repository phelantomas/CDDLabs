// SafeBuffer.cpp --- 
// 
// Filename: SafeBuffer.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Sat Jan  6 15:13:11 2018 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Sat Jan  6 15:13:46 2018 (+0000)
//           By: Tomas Phelan
//     Update #: 4
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

#include "SafeBuffer.h"

SafeBuffer::SafeBuffer(int size){
  buffer_size = size;
  lock = std::make_shared<Semaphore>(1);
  occupied = std::make_shared<Semaphore>(0);
  available = std::make_shared<Semaphore>(buffer_size);
}

int SafeBuffer::size(){
  return buffer.size();
}

void SafeBuffer::enqueue(char c){
  available->Wait();
  lock->Wait();
  buffer.push(c);
  lock->Signal();
  occupied->Signal();
}

char SafeBuffer::dequeue(){
  occupied->Wait();
  lock->Wait();
  char c = buffer.front();
  buffer.pop();
  lock->Signal();
  available->Signal();
  return c;
}

// 
// SafeBuffer.cpp ends here
