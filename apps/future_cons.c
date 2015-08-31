#include<stdio.h>
#include<stdlib.h>
#include<future.h>
#include<thread.h>

uint future_cons(future *fut) {
  	int i;
	irqmask mask;
	//status = future_get(fut,&i);
	if(fut->flag == FUTURE_EXCLUSIVE) {
  		while(future_get(fut,&i) == -1) {
			suspend(gettid());
  		}
  	}
  	if(fut->flag == FUTURE_SHARED) {
		while(future_get(fut,&i) == -1) {
			suspend(gettid());
		}
  	}
  	if(fut->flag == FUTURE_QUEUE) {
  		while(future_get(fut,&i) == -1) {
  			suspend(gettid());
  		}
  	}
	mask =disable();
  	printf("it produced %d\n", i);
  	restore(mask);
	return OK;
	}
