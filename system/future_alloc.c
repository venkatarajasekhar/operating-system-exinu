#include <thread.h>
#include <future.h>
#include <interrupt.h>
#include <platform.h>

future* future_alloc(int future_flags){ 

    if(future_flags == FUTURE_EXCLUSIVE){
        future *f = (future*)memget(sizeof(future));
        f->state = FUTURE_EMPTY;
        f->value = 0;
        f->flag = FUTURE_EXCLUSIVE;
        f->tid = -1;
        f->get_queue.head = NULL;
        f->get_queue.tail = NULL;
        f->set_queue.head = NULL;
        f->set_queue.tail = NULL;
        return f;
    }
    if(future_flags == FUTURE_SHARED){
        future *f = (future*)memget(sizeof(future));
        f->state = FUTURE_EMPTY;
        f->value = 0;
        f->flag = FUTURE_SHARED;
        f->tid = -1;
        f->get_queue.head = NULL;
        f->get_queue.tail = NULL;
        f->set_queue.head = NULL;
        f->set_queue.tail = NULL;
        return f;
    }
    if(future_flags == FUTURE_QUEUE){
        future *f = (future*)memget(sizeof(future));
        f->state = FUTURE_EMPTY;
        f->value = 0;
        f->flag = FUTURE_QUEUE;
        f->tid = -1;
        f->get_queue.head = NULL;
        f->get_queue.tail = NULL;
        f->set_queue.head = NULL;
        f->set_queue.tail = NULL;
        return f;
    }
    return NULL;
}