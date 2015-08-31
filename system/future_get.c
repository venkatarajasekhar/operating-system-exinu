#include <thread.h>
#include <future.h>
#include <interrupt.h>
#include <platform.h>
#include <shell.h>


syscall future_get(future *f, int *val){
    irqmask mask;
    mask = disable();
  
    if(f == NULL) {
        restore(mask);
        return SYSERR;
    }
    if(f->flag == FUTURE_EXCLUSIVE){
        if (f->state == FUTURE_VALID) { 
            *val = f->value;
            f->state = FUTURE_EMPTY;
            restore(mask);
            return OK;
        }
        else {
            
            f->tid = gettid();
            f->state = FUTURE_WAITING;
            restore(mask);
            return SYSERR;
        }
    }
    if(f->flag == FUTURE_SHARED){
        if(f->state != FUTURE_VALID) {
            f->state = FUTURE_WAITING;
            en_queue(&(f->get_queue), gettid());
            restore(mask);
            return SYSERR;
        }
        *val = f->value;
        if(!emp_queue(&(f->get_queue))) {
            
            peek_queue(&(f->get_queue));
            resume(del_queue(&(f->get_queue)));
        }
        restore(mask);
        return OK;
    }
    if(f->flag == FUTURE_QUEUE){
        if(f->state == FUTURE_VALID && gettid() == f->tid) {
            *val = f->value;
            restore(mask);
            return OK;
        }
     
        en_queue(&(f->get_queue), gettid()); 
        f->state = FUTURE_WAITING;
        if(!emp_queue(&(f->set_queue))) {
            resume(del_queue(&(f->set_queue)));   
        }
        restore(mask);
        return SYSERR;
    }
    restore(mask);
    return SYSERR;
}
