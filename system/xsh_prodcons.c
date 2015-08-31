/**
 *@file xsh_prodcons.c
 *
 */


#include <prodcons.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <future.h>
#include <semaphore.h>
/**
 * @ingroup shell
 * 
 * Shell command (prodcons).
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */

int n; //Definition for global variable 'n'

semaphore consumed, produced; //Definition for semaphores

/*Now global variable n will be on Heap so it is accessible to all the processes i.e. consume() and produce()*/

int number_only(const char *s)
{
    while(*s)
    {
	if(isdigit(*s++) == 0) 
	    return 0;
    }
    return 1;
}

shellcmd xsh_prodcons(int nargs, char *args[])
{
    //Argument verifications and validations
	

    //This code block is for HW4
/*    if(nargs == 2 && strcmp(args[1], "-f") == 0)
    {
        future *f1, *f2, *f3;
        f1 = future_alloc(FUTURE_EXCLUSIVE);
        f2 = future_alloc(FUTURE_EXCLUSIVE);
        f3 = future_alloc(FUTURE_EXCLUSIVE);
        resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
        resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
        resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
        resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
        resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
        resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
        return OK;
    }
*/
  
    //This code block is for HW5

    if(nargs == 2 && strcmp(args[1], "-f") == 0)
    {
        future *f_exclusive, *f_shared, *f_queue;
     
        f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
        f_shared = future_alloc(FUTURE_SHARED);
        f_queue = future_alloc(FUTURE_QUEUE);
    
        //TEST FUTURE_EXCLUSIVE
        resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
        resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );

        //TEST FUTURE_SHARED
        resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
        resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
        resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
        resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
        resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

        //TEST FUTURE_QUEUE
        resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
        resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
        resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
        resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
        resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
        resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
        resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
        resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
	return OK;
    }


    /*Output help, if '--help' argument was supplied */
    if (nargs == 2 && strcmp(args[1], "--help") == 0)
    {
        printf("Usage: %s\n\n", args[0]);
        printf("Description:\n");
        printf("\tCrete 2 processes which can exchange data using global variables\n");
        printf("Options:\n");
        printf("\t--help\tdisplay this help and exit\n");
	printf("\tInt(Optional)\tInt is an Integer which is a global variable\n");
        return OK;
    }

    /* Check for correct number of arguments */
    if (nargs > 2)
    {
        fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
    }
    
    //check args[1] if present assign value to count
    if (nargs == 2 && !number_only(args[1]))
    {
        fprintf(stderr, "%s: is not a valid positive number\n", args[1]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;

    }
  
    int count;

    if (nargs < 2)
        count = 2000; //local variable to hold count	
    else
	count = atoi(args[1]);

    //printf("The value of args[1] is %d\n", count);


    /*Initialize semaphores*/
    consumed = semcreate(1);
    produced = semcreate(0);
  
    //create the process producer and consumer and put them in ready queue.
    //Look at the definition of function create and resume in exinus/system folder for reference
   
    resume( create(producer, 1024, 20, "producer", 1, count));
    resume( create(consumer, 1024, 20, "consumer", 1, count));
}
