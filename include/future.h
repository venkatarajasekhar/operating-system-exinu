#ifndef _FUTURE_H_
#define _FUTURE_H_

#include <stddef.h>
#include<stdlib.h> 
/* define states */
#define FUTURE_EMPTY	  0
#define FUTURE_WAITING 	  1         
#define FUTURE_VALID 	  2         

/* modes of operation for future*/
#define FUTURE_EXCLUSIVE  1	
#define FUTURE_SHARED     2	    
#define FUTURE_QUEUE      3     

typedef struct Node
{
        tid_typ thread_id;
        struct Node *next;
} qnode;

typedef struct fqueue
{
        qnode *head;
        qnode *tail;
} queue;
typedef struct futent
{
   int value;
   int flag;
   int state;
   tid_typ tid;
   queue get_queue;
   queue set_queue;

} future;
extern semaphore consumed, produced;

uint future_prod(future*);
uint future_cons(future*);


/* Interface for system call */
future* future_alloc(int future_flags);
syscall future_free(future*);
syscall future_get(future*, int*);
syscall future_set(future*, int*);

//we define a queue structure and queue function for the code

void crea_queue(queue *);
void en_queue(queue *, tid_typ);
tid_typ del_queue(queue *);
int emp_queue(queue *);
void clear_queue(queue *);
int peek_queue(queue *);
int coun_queue(queue *);
#endif /* _FUTURE_H_ */
