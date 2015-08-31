#include<stdio.h>
#include<stdlib.h>
#include<future.h>




uint future_prod(future *fut) {
  	int i, j;
  	j = (int)fut;
  	for (i=0; i<1000; i++) {
    	j += i;
  	}
  	j -= fut->tid;
  	
  	if(fut->flag == FUTURE_EXCLUSIVE) {
  		sleep(10);
		future_set(fut, &j);  		
  	}
  	if(fut->flag == FUTURE_SHARED) {
  		future_set(fut, &j);
  	}
  	
  	if(fut->flag == FUTURE_QUEUE) {
  		while(future_set(fut, &j) == -1) {
  			suspend(gettid());
  		}
  	}
  	return OK;
}
