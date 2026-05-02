/*
 * mutex_queue.c
 *
 *  Created on: Apr 30, 2026
 *      Author: Netcom
 */


#include"stm32f401xe.h"
#include"mutex_queue.h"
#include"OSKernal.h"




void mutex_init(mutex_t *m)
{
	m->locked=0;
	m->owner=0;
	m->head=NULL;
	m->tail=NULL;
}

void mutex_enqueue(mutex_t *m,tcb *task){

	task->waiting_task=NULL;

	if(!task)
	{
		return;
	}

	if(m->head==NULL)
	{
		m->head=task;
		m->tail=task;
	}
	else
	{
		m->tail->waiting_task=task;
		m->tail=task;
	}

}

tcb *mutex_dequeue(mutex_t *m){

	tcb *task= m->head;

	if(task){
		m->head=task->waiting_task;
		if(m->head==NULL)
		{
			m->tail=NULL;
		}
	}
	return task;
}

void mutex_lock(mutex_t *m)
{
    __disable_irq();

    if(m->locked == 0)
    {
        m->locked = 1;
        m->owner = currentptr;
        __enable_irq();
        return;
    }

    // block task
    currentptr->state = BLOCKED;
    mutex_enqueue(m, currentptr);

    __enable_irq();


}



void mutex_unlock(mutex_t *m)
{
    __disable_irq();

    if(m->owner != currentptr)
    {
        __enable_irq();
        return;
    }

    tcb *next = mutex_dequeue(m);

    if(next)
    {
        next->state = READY;
        m->owner = next;
        m->locked = 1;
    }
    else
    {
        m->locked = 0;
        m->owner = NULL;
    }

    __enable_irq();
}

