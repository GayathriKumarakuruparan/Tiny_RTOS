/*
 * OSKernal.h
 *
 *  Created on: Apr 21, 2026
 *      Author: Netcom
 */

#ifndef OSKERNAL_H_
#define OSKERNAL_H_

void OsKernal_init(void);
uint8_t osKernelAddThreads(void (*task0)(void), void (*task1)(void), void (*task2)(void));
void OsKernalLaunch(uint8_t quant);
void osScheduleLaunch(void);

void osSelectNextTask(void);


#define		READY				0
#define 	BLOCKED 			0


#endif /* OSKERNAL_H_ */
