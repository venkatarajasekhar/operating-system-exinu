#include<stdio.h>
#include<stdlib.h>
#include<future.h>
#include<stddef.h>

void crea_queue(queue *new) {
    new -> head = NULL;
    new -> tail = NULL;
}

void en_queue(queue *q, tid_typ tid) {
    qnode *new_node = (qnode *)malloc(sizeof(qnode));
    new_node -> thread_id = tid;
    new_node -> next = NULL;
    if(q->tail == NULL){
        q -> head = q -> tail = new_node;   
    }
    else{
        q->tail =  (q->tail)->next = new_node;
    }
}

tid_typ del_queue(queue *q) {
    qnode *t;
    tid_typ tem_tid;
    if(q -> head == NULL) {
        return -1;
    }
    else {
        t = q -> head;
        tem_tid = q -> head ->thread_id;
        q->head = t->next;
    }
    if(q->head == NULL){
        q->tail = NULL;
    }
    free(t);
    return tem_tid;
}

tid_typ peek_queue(queue *q) {
    if(q->head == NULL) {
        return -1;
    }
    else {
        return q->head->thread_id;
    }
}

int emp_queue(queue *q){
    if(q->head == NULL && q->tail == NULL){
        return 1;
    }
    return 0;
}
void clear_queue(queue *q){
    qnode *p = q->head;
    while(p!=NULL){
        q->head=q->head->next;
        free(p);
        p = q->head;
    }
    q->tail = NULL;
    return;
}

int coun_queue(queue *q) {
    int count = 0;
    qnode *t = q->head;
    while(t != NULL)
        count++;
    return count;
}
