# Lab One – Signalling with Semaphores
In real life a semaphore is a system of signals used to communicate visually, usually with ﬂags, lights, or some other mechanism. In software, a semaphore is a data structure that is useful for solving a variety of synchronization problems. Semaphores were invented by Edsger Dijkstra, a famously eccentric computer scientist. Some of the details have changed since the original design, but the basic idea is the same.

Possibly the simplest use for a semaphore is signaling, which means that one thread sends a signal to another thread to indicate that something has happened. Signaling makes it possible to guarantee that a section of code in one thread will run before a section of code in another thread; in other words, it solves the serialization problem. 

This code shall demonstrate the concept. 

Files
-------------


> **signal.cpp**
>
> - This is the main application source file.
>
> **Semaphore.cpp**
> - This contains the main implentation for the semaphore.
>
>**Semaphore.h**
>- Contains the definitions of the semaphore.


