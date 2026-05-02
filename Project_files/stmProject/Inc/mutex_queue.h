/*
 * mutex_queue.h
 *
 *  Created on: Apr 30, 2026
 *      Author: Netcom
 */

#ifndef MUTEX_QUEUE_H_
#define MUTEX_QUEUE_H_

#include <stddef.h>
typedef struct tcb{
	int32_t *stackpointer;
	struct tcb *next_task;
	struct tcb *waiting_task;
	uint32_t state;
} tcb;
extern tcb *currentptr;

typedef struct{
	uint8_t locked;
	tcb	*owner;
	tcb *head;
	tcb *tail;
}mutex_t;
void mutex_unlock(mutex_t *m);
void mutex_lock(mutex_t *m);
tcb *mutex_dequeue(mutex_t *m);
void mutex_enqueue(mutex_t *m,tcb *task);
void mutex_init(mutex_t *m);


#endif /* MUTEX_QUEUE_H_ */
