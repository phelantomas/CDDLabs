// Prodcon.cpp --- 
// 
// Filename: Prodcon.cpp
// Description: 
// Author: Tomas Phelan
// Maintainer: 
// Created: Wed Oct 25 12:42:02 2017 (+0100)
// Version: 
// Package-Requires: ()
// Last-Updated: Wed Jan 31 12:43:36 2018 (+0000)
//           By: Tomas Phelan
//     Update #: 39
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

#include <iostream>
#include <memory>
#include "SafeBuffer.h"
#include <vector>
#include <thread>
#include <map>

std::map<char,int>  characterCount;

/*! 
brief: Add charcter to buffer
parameters: buffer, character
*/
void produce(std::shared_ptr<SafeBuffer> buffer, char character){
  std::cout << "Producing : " << character << std::endl;
  buffer->enqueue(character);
}

/*! 
brief: Removes character from buffer
parameters: buffer
*/
void consume(std::shared_ptr<SafeBuffer> buffer){
  char removedChar;
  
  removedChar = buffer->dequeue();
  characterCount[removedChar]++;
  std::cout << "Consuming : " << removedChar << std::endl;
}

/*! 
brief: Returns a character
parameters:
*/
char generate_char(){
  char randomChar;

  randomChar = std::rand() % 26 + 97;
  return randomChar;
}

int main() {

  //initiliase
  for(char i = 97; i < 123; ++i) {
    characterCount[i] = 0;
  }

  int numberOfChars = 0;
  char randomChar;
  std::cout << "Enter in number of random characters wanted: ";
 
  while(!(std::cin >> numberOfChars)){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input.  Try again: ";
  }
  std::cout << "You entered: " << numberOfChars << std::endl;

  std::shared_ptr<SafeBuffer> buffer(new SafeBuffer(10));

  std::thread thread_produce;
  std::thread thread_consume;

  for(int i = 0; i < numberOfChars; ++i){
    randomChar = generate_char();
     
    thread_produce = std::thread(produce, buffer, randomChar);
    thread_consume = std::thread(consume, buffer);

    thread_consume.join();
    thread_produce.join();
  }

  thread_produce = std::thread(produce, buffer, 'X');
  thread_consume = std::thread(consume, buffer);

  thread_consume.join();
  thread_produce.join();
  
  std::cout << std::endl;
  //initiliase
  for(char i = 97; i < 123; ++i) {
    if(characterCount[i] > 0){
      std::cout << i << " showed up : " << characterCount[i]  << std::endl;
    }
  }
  
  return 0;
}

// 
// Prodcon.cpp ends here
