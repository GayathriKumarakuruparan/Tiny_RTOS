#include "stm32f401xe.h"
#include "mutex_queue.h"
#include "OSKernal.h"

/* -------------------------
   Init mutex
   ------------------------- */
void mutex_init(mutex_t *m)
{
    m->locked = 0;
    m->owner  = NULL;
    m->head   = NULL;
    m->tail   = NULL;
}

/* -------------------------
   Add blocked task to queue
   ------------------------- */
void mutex_enqueue(mutex_t *m, tcb *task)
{
    if(task == NULL)
        return;

    task->waiting_task = NULL;

    if(m->head == NULL)
    {
        m->head = task;
        m->tail = task;
    }
    else
    {
        m->tail->waiting_task = task;
        m->tail = task;
    }
}

/* -------------------------
   Remove first waiting task
   ------------------------- */
tcb *mutex_dequeue(mutex_t *m)
{
    tcb *task = m->head;

    if(task != NULL)
    {
        m->head = task->waiting_task;
        task->waiting_task = NULL;

        if(m->head == NULL)
        {
            m->tail = NULL;
        }
    }

    return task;
}

/* -------------------------
   Lock mutex
   ------------------------- */
void mutex_lock(mutex_t *m)
{
    __disable_irq();

    /* free mutex */
    if(m->locked == 0)
    {
        m->locked = 1;
        m->owner  = currentptr;

        __enable_irq();
        return;
    }

    /* already locked -> block current task */
    currentptr->state = BLOCKED;

    mutex_enqueue(m, currentptr);

    __enable_irq();

    /* immediate context switch */
    SCB->ICSR |= (1U << 28);


}

/* -------------------------
   Unlock mutex
   ------------------------- */
void mutex_unlock(mutex_t *m)
{
    __disable_irq();

    /* only owner can unlock */
    if(m->owner != currentptr)
    {
        __enable_irq();
        return;
    }

    tcb *next = mutex_dequeue(m);

    if(next != NULL)
    {
        /* give mutex directly to next waiting task */
        next->state = READY;
        m->owner    = next;
        m->locked   = 1;
    }
    else
    {
        /* nobody waiting */
        m->locked = 0;
        m->owner  = NULL;
    }

    __enable_irq();
}
