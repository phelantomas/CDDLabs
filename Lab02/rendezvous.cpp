#include "Semaphore.h"
#include <iostream>
#include <thread>
//Task: B1 always print before A2, and A1 always print before B2. 

void taskOne(std::shared_ptr<Semaphore> taskOneSem,std::shared_ptr<Semaphore> taskTwoSem){
  std::cout << "A1 Prints Before B2 "<<std::endl;
  //Will now allow B2 to print
  taskOneSem->Signal();
  taskTwoSem->Wait();
  std::cout << "A2 Prints After B1 "<<std::endl;
}
void taskTwo(std::shared_ptr<Semaphore> taskOneSem,std::shared_ptr<Semaphore> taskTwoSem){
  std::cout << "B1 Prints Before A2 "<<std::endl;
  taskTwoSem->Signal();
  //Will prevent B2 from printing if not A1 has not already printed
  taskOneSem->Wait();
  std::cout << "B2 Prints After A1 "<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> taskOneSem( new Semaphore);
  std::shared_ptr<Semaphore> taskTwoSem( new Semaphore);
  std::cout << "Task: B1 always print before A2, and A1 always print before B2.\n";
  /**< Launch the threads  */
  threadOne=std::thread(taskOne, taskOneSem, taskTwoSem);
  threadTwo=std::thread(taskTwo, taskOneSem, taskTwoSem);

  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
