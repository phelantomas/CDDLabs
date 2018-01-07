#include "Semaphore.h"
#include <iostream>

/*!
 * \class Semaphore 
 * \brief Using counter variable, mutex and condition variable
*/


//! \fn Semaphore Wait method locks the thread and decrement counter 
void Semaphore::Wait(){
  std::unique_lock< std::mutex > lock(mutex);
  condition.wait(lock, [&]()-> bool {return counter > 0 ;}); 
  --counter;
};

//! \fn Semaphore Signal method incremet counter and release one thread
void Semaphore::Signal(){
  std::unique_lock< std::mutex > lock(mutex);
  counter++;
  condition.notify_one();
};