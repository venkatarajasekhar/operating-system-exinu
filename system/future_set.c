#include <thread.h>
#include <future.h>
#include <interrupt.h>
#include <platform.h>



 syscall future_set(future *f, int *i) {
    irqmask mask;
    mask = disable();
    if(f == NULL){
        restore(mask);
        return SYSERR;
    }
    if(f->flag == FUTURE_EXCLUSIVE) {
        if(f->state == FUTURE_WAITING) {
          
            f->value = *i;
            f->state = FUTURE_VALID; 
            resume(f->tid);
            restore(mask);
            return OK;
        }
        f->value = *i;
        f->state = FUTURE_VALID; 
        restore(mask);
        return OK;
    }
    if(f->flag == FUTURE_SHARED) {
        if(f->state == FUTURE_VALID) {
            printf("Producer already set, Error!\n");
            restore(mask);
            return SYSERR;
        }
        f->state = FUTURE_VALID;
        f->value = *i;
        if(!emp_queue(&(f->get_queue))){
             peek_queue(&(f->get_queue));
            resume(del_queue(&(f->get_queue)));
        }
        restore(mask);
        return OK;
    }
    if(f->flag == FUTURE_QUEUE){
        if(emp_queue(&(f->get_queue))) {
            en_queue(&(f->set_queue), gettid());
            restore(mask);
            return SYSERR;
        }
        else {
            f->state = FUTURE_VALID;
            f->value = *i;
            f->tid = peek_queue(&(f->get_queue));
            resume(del_queue(&(f->get_queue)));
            restore(mask);
            return OK;  
        }
        return OK;
    }
    restore(mask);
    return SYSERR;
}
