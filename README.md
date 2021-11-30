### Banker's Algorithm
# Introduction
A Banker's algorithm is used to test if the system is an safe or unsafe state. An unsafe state occurs when there is a possibility of deadlock (i.e. all processes are waiting on another process)

There are 4 basic requirements necessary for deadlock to occur.
Mutual exclusion: Only one process can use a resource at a time
Hold and wait: A process holding a resource is simultaneously requesting another
No preemption: A resource may only be accessed once the process holding that resource is done using it.
Circular wait: There exists a set of condtions where P0 is waiting on P1, P1 is waiting on P2, etc.

These 4 conditions are necessary but not sufficient for deadlock to occur.

# Background Information

There may exist n resource types (e.g. CPU, memory, storage, etc.) and m resource instances of a resource. There also may exist p processes sharing those resources.

There are 4 different types of resource vectors:
Available: the resources the system has available currently
Maximum: the maximum resources a process needs to finish its task (this is determined in advance of starting the process)
Allocation: the resources a process is using (holds) currently
Need: the additional resources a process needs in order to finish its task

Need = Maximum - Allocation

# Algorithm
The central idea of this problem is that the banker's algorithm tests if it can exit a seemingly possible deadlock.
All processes are running currently, and the system must give its resources to a process that can finish its task and free up its resources for other processes to use.

A help analog would be untying a tangle of strings/cords or the pick up stick game (where one must carefully find a free point to loosen up the mess)
If the algorithm is unable to find a way out to free all the processes, the system is officially in an unsafe state and will be in a deadlock.
This algorithm is implemented when a process requests resources to ensure that fulfilling the request will not result in the an eventual deadlock.

1. Finish vector with size p initialized with all false values to indicate all running processes as not finished
2. Find an unfinished process (i.e. finish<sub>i<sub> == false) where Need<sub>i<sub> <= Available. If not found, skip to step 4.
3. Available = Available + Allocation<sub>i<sub>. 
  *
                                                                                                 

Semaphores are used to prevent reckless production or consumption, including:
1. Producing when shared memory block is full
2. Consuming when shared memory block is empty
3. Producing and consuming in the shared memory block at the same time

Semaphores offer protections with its sem_wait() and sem_post() functions.
sem_wait() pauses the thread if the semaphore value is 0, while sem_post() increases the semaphore value by 1.
As semaphores can be accessed across processes, they allow for process synchronization.

Using these two methods, one can code it so that a process must wait until another one finishes a task (sem_wait() occurs until another thread runs sem_post()).
This allows for process management.

## Steps to run a local copy of this program

# Setup
Compile using Linux
* e.g.
    * install VirtualBox
    * install Ubuntu 20.04 on VirtualBox
    * install Virtual Studio Code on Ubuntu

Additional prerequisties:
* gcc
``` 
sudo apt-get install gcc 
```

Copy this repository's link for this program
```
git clone https://github.com/davidbian1/OS.git 
```

# Compilation
Commands for compilation:

```
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer
./producer & ./consumer &
```

# Output
Expected Sample Output
```
Consumer ready to receive 20 items.

Producer ready to create 20 items.
Item produced, there are now 1 item(s) in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item consumed, there are now 0 item(s) remaining in the table.
Item produced, there are now 1 item(s) in the table.
Item consumed, there are now 0 item(s) remaining in the table.
Item produced, there are now 1 item(s) in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item consumed, there are now 0 item(s) remaining in the table.
Item produced, there are now 1 item(s) in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item consumed, there are now 0 item(s) remaining in the table.
item produced, there are now 1 item(s) in the table.
Item consumed, there are now 0 item(s) remaining in the table.
Item produced, there are now 1 item(s) in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item consumed, there are now 0 item(s) remaining in the table.
Item produced, there are now 1 item(s) in the table.
Item consumed, there are now 0 item(s) remaining in the table.
Item produced, there are now 1 item(s) in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
item produced, there are now 2 item(s) in the table.
Item consumed, there are now 1 item(s) remaining in the table.
Item consumed, there are now 0 item(s) remaining in the table.
Producer cleaned up!
Consumer cleaned up!
```

# Work and Acknowledgements
Thank you to Dr. Qiang Guan for supplying his example code.
* Most of the code orginates from his code, with a few tweaks here and there
* Work done by me were mainly the dense comments explaining each line of code and how they worked to demonstrate my thorough understanding of the code.
* If the code does not compile, it is likely due to the sem_post() and sem_wait() functions.
   * When I was running the code and with debugging, I found that the threads would hang on the sem_post() and sem_wait() functions (as well as sem_init()), 
   * resulting in a segmentation error when I exited it. 
      * I found no clear answer as to why this occurs (I searched quite a lot online about it), as a simple semaphore declaration and sem_post() hangs the thread, despite a correct initalization of the semaphore. If you could find why this occurs (and how to fix), I would much appreciate it (I spent several hours trying to resolve it.)
   * Most examples of the consumer-producer problem dealt with 2+ threads in a single problem, so I found them not useful applying for the multi-program requirement for this programming assignment.
