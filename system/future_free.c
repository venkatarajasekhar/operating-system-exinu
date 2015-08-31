#include <thread.h>
#include <future.h>
#include <interrupt.h>
#include <platform.h>

syscall future_free(future *f)
{
    irqmask mask;
    mask = disable();
    
    if(f == NULL){
        restore(mask);
        return SYSERR;
    }
    f->state = FUTURE_EMPTY;
    clear_queue(&(f->get_queue));
    clear_queue(&(f->set_queue));
    free(&(f->get_queue));
    free(&(f->set_queue));
    memfree(f, sizeof(future));
    restore(mask);
    return OK;
}
