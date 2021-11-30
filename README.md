### Banker's Algorithm
# Introduction
A Banker's Algorithm is used to test if the system is an safe or unsafe state. An unsafe state occurs when there is a possibility of deadlock (i.e. all processes are such that each is waiting on another process). The algorithm's name derives from a banker lending out money so it can be repaid with interest, which in turn can be used to lend other people money so they can repay their loans.

There are 4 basic requirements necessary for deadlock to occur.
* Mutual exclusion: Only one process can use a resource at a time.
* Hold and wait: A process holding a resource is simultaneously requesting another.
* No preemption: A resource may only be accessed once the process holding that resource is done using it.
* Circular wait: There exists a set of condtions where P<sub>0</sub> is waiting on P<sub>1</sub>, P<sub>1</sub> is waiting on P<sub>2</sub>, etc.

These 4 conditions are necessary but not sufficient for deadlock to occur.

# Background Information

There may exist m resource types (e.g. CPU, memory, storage, etc.) and n resource instances of a given resource. 
There also may exist p processes competing for those resources. All resources are considered reusable by the processes.

There are 4 different types of resource vectors in the Banker's Algorithm:
* Available: the resources the system has available currently
* Max: the maximum resources a process needs to finish its task (this is determined in advance, before the process starts)
* Allocation: the resources a process is using (holds) currently
* Need: the additional resources a process may need in order to finish its task

Need = Max - Allocation

# Algorithm
The central idea of this problem is that the banker's algorithm tests if a system at a given state can exit a seemingly inevitable deadlock.
All processes are running currently, and the system must lend its resources to a process that can finish its task in order to free up additional resources for other processes to use.

A helpful analog would be untying a tangle of strings/cords or the pick up stick game (one must carefully find and detach a free point in order to untangle the mess).

If the algorithm is unable to find a way out to free all the processes, the system is officially in an unsafe state and will be in a deadlock.
This algorithm is implemented when a process requests resources to ensure that the system state will not be in one where fulfilling the request will result in an eventual deadlock.

Steps:
1. Initialize a vector Finish with size p such that all elements of the vector are false. This vector indicates the status of all processes in the algorithm.
2. 
   * Find an unfinished process (i.e. finish<sub>i</sub> == false) where Need<sub>i</sub> <= Available 
     (i is the process index, starting from 0 and going to PROCESS_COUNT - 1).
   * If not found, skip to step 4.
3.
   * Available = Available + Allocation<sub>i</sub>. 
   * Finish<sub>i</sub> = true. Repeat step 2.
4. If all values in Finish equal true, all processes can finish and thus the system is in a safe state.

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
git clone https://github.com/davidbian1/OS2.git 
```

# Compilation
Commands for compilation:

```
gcc bankersalgorithm.c -o bankersalgo
./bankersalgo
```

# Output
Expected Output
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

# Customization
The .c code may be modified for different values of m, n, and p (resource_type, instances, and processes).
* m and p are declared as constants in the .c code and may be freely changed to fit the given situation.

e.g.
```
#define RESOURCE_TYPES m
```
* If m, n, and/or p are changed, the changes must be reflected in the input file.

## Input File Requirements
* The .c file parses an input text file and reads in a series of numbers.
    * The total count of numbers must be equal to m × p × 2 + m.
    * Numbers must be have whitespace between them; otherwise they will be treated as one number.
    * Nonnumerical text is ignored entirely
        * Numbers in the names of processes (e.g. P<sub>0</sub>) and others will be extracted and treated as resource instances
    * Numbers must be in order (for resources, processes, and resource_type)
        * 1. First m numbers are the instance counts for Available (in order of resource_type)
        * 2. Next m numbers are the instance counts for Allocation for process P<sub>0</sub> (in order of resource_type)
        * 3. Next m numbers are the instance counts for Max for process P<sub>0</sub> (in order of resource_type)
        * 4. Repeat steps 2 and 3 for P<sub>i</sub> where i goes from 1 to PROCESS_COUNT - 1
 
## Customizing Input File
* The input file is a .txt file with name input and iniitialized resource instance values.
 * The input file name may freely be changed by changing the name of the input file AND the name of the file read in from the .c file
### Importing a downloaded text file
Install wget
```
sudo apt install wget
```
Import downloaded file
```
wget URL
```
### Creating a text file
Create .txt file
```
touch name.txt
```
Edit the text file
```
nano name.txt
```
