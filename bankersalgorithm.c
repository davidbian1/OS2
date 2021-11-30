#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//Constants -- feel free to change these as you see fit for your input file(s)
#define RESOURCE_TYPES 3 // currently A, B, and C
#define PROCESS_COUNT 5 // currently P0, P1, P2, P3, and P4
#define STRING_LENGTH 1024 // max size of strings read from input file

//psuedo-class in C (resource vector)
struct Resources
{
    int resource[RESOURCE_TYPES]; //contains resource info

  //Functions to operate on the Resources structure
    bool (*encapsulate) (struct Resources wrapper, struct Resources wrappee);
    struct Resources (*subtract) (struct Resources minuend, struct Resources subtrahend);
    struct Resources (*add) (struct Resources addend, struct Resources addee);
};

//contains three resource strctures (named appropriately)
struct Process
{
    struct Resources allocation; //resources allocated to process currently
    struct Resources max; //maximum number of resources to complete its task
    struct Resources need; //resources process will need to request in the future
};

//Evaluates if wrapper has a corresponding resource for every resource wrappee has
bool resources_encapsulate (struct Resources wrapper, struct Resources wrappee)
{
    //If wrapper has greater or equal amounts of each resource type than wrappee
    for (int i = 0; i < RESOURCE_TYPES; ++i)
    {
        if (wrapper.resource[i] < wrappee.resource[i])
          { return false;}
    }
    return true;
}

//Returns the difference of two resource structures (each resource type resolved individually)
struct Resources resources_subtract (struct Resources minuend, struct Resources subtrahend)
{
    struct Resources difference;

    for (int i = 0; i < RESOURCE_TYPES; ++i)
    {
        difference.resource[i] = minuend.resource[i] - subtrahend.resource[i];
    }
    return difference;
}

//Returns the sum of two resource structures (each resource type resolved individually)
struct Resources resources_add (struct Resources addend, struct Resources addee)
{
    struct Resources sum;

    for (int i = 0; i < RESOURCE_TYPES; ++i)
    {
        sum.resource[i] = addend.resource[i] + addee.resource[i];
    }

     return sum;
}


//Main
int main()
{
  //Vars
    //Number of failed attempts
    int failedAttempts = 0;
    //Number of finished processes
    int finishedProcesses = 0;
    //Number of processes not finished
    int remainingProcesses = PROCESS_COUNT;

    //counter
    int i = 0;

    //structure for resources available
    struct Resources available;

    struct Process processes[PROCESS_COUNT];


  //Read resources values in from text file and initalize processes

    FILE *input;
    input = fopen("input.txt", "r"); // open file with said name -- currently input.txt

    //Number of nums to read in
    const int SIZE = PROCESS_COUNT * RESOURCE_TYPES * 2 + RESOURCE_TYPES;
      /*Number of peocesses * number for each resource type *
        2 (allocation and max) + number of resource types (available sturct)
      */

    //To hold nums temporarily
    int nums[SIZE];

    //Character variable to read in
    char c;

    //Converted -- int value of character, total -- to keep track of total numerical value
    int converted, total = 0;

    //If char read in is number
    bool number = false;

    //If file does not open correctly
    if (input == NULL)
        {printf("Invalid file\n"); exit(0);}


    while (i < SIZE)
    {
        //Get character from file
        c = fgetc(input);

        //Covert character to int
        converted = (int) c - (int) '0';

        //If coverted character is a number
        if (converted > -1 && converted < 10)
        {
             //add to total value
             total *= 10;
             total += converted;
             number = true;
        }
        else
        {
             //If number
             if (number)
             {
                 //store in array
                 nums[i] = total;
                 ++i;
                 //reset number
                 number = false;
	     }
             //reset total
             total = 0;
        }
    }

    //Close input file
    fclose(input);

    //Initialize avaiable resource struct
    for (i = 0; i < RESOURCE_TYPES; ++i)
    {
        available.resource[i] = nums[i];
    }

    //Initialize each process
    for (int j = 0; j < PROCESS_COUNT; ++j)
    {
        //Initialize allocation resource 
        for (int k = 0; k < RESOURCE_TYPES; ++k,++i)
        {
             processes[j].allocation.resource[k] = nums[i];
        }
        //Initialize max resources
        for (int k = 0; k < RESOURCE_TYPES; ++k,++i)
        {
             processes[j].max.resource[k] = nums[i];
        }
        //Initialize need resources
        processes[j].need = resources_subtract(processes[j].max, processes[j].allocation);
    }

    //Array for processes finished or not
    bool finish[PROCESS_COUNT];

    //Initialize array for all false values
    for (int j = 0; j < PROCESS_COUNT; ++j)
    {
        finish[j] = false;
    }

    //Array to hold process order for safe sequence
    int order[PROCESS_COUNT];

    //Reset counter
    i = 0;




//Banker's algorithm

  //While not failed too many times and not done (exist unfinished processes)
  while (failedAttempts < remainingProcesses && finishedProcesses < PROCESS_COUNT)
  {
        //Skip finished processes
        if (!finish[i])
        {
            // +1 to atttempts
            ++failedAttempts;
            // check if need <= available
            if (resources_encapsulate(available, processes[i].need))
            {
                //If so
                finish[i] = true; //finish process
                order[finishedProcesses] = i; //Keep track of process number
                available = resources_add(available, processes[i].allocation); //update available resources
                ++finishedProcesses;
                --remainingProcesses;
                //Reset fails
                failedAttempts = 0;
            }
        }
        //Go to next process
        ++i;
        i %= 5;
  }



//Output result

  //If all processes finished
  if (remainingProcesses == 0)
  {
        printf("System in SAFE state!\n");
        printf("Safe sequence: ");
        //Print safe sequence
        for (i = 0; i < PROCESS_COUNT; ++i)
        {
            printf("P%d ", order[i]);
        }
  }
  else
  {
        printf("System in UNSAFE state!\n");
  }

  return 0;
}
