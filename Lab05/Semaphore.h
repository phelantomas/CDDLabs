#include <mutex>
#include <condition_variable>

/*!
 *  \class Semaphore
 *  \brief Semaphore implementation 
 * 
 *  Using counter, mutex and condition variable 
 */
class Semaphore{

private:
  int counter;
  std::mutex mutex; 
  std::condition_variable condition; 

 public:
  Semaphore(int count=1): counter(count){};
  void Wait();
  void Signal();
};