#include<stm32f401xe.h>
#include<stdint.h>

#define 	NUMBER_OF_TASK		3
#define		SYS_CLK				16000000
#define 	NUMBER_OF_ELEMENT	400
#define		SYSTICK_CLKSOURCE	(1U<<2)
#define		SYSTICK_ENABLE		(1U<<0)
#define 	SYSTICK_TICKINT		(1U<<1)


#define 	SYSTICK_CLEAR		0


typedef struct tcb{
	int32_t *stackpointer;
	struct tcb *next_task;
} tcb;

tcb	task_control_block[NUMBER_OF_TASK];
tcb *currentptr;
uint32_t MILLI_PRESCALAR;

int32_t TcbStack[NUMBER_OF_TASK][NUMBER_OF_ELEMENT];

uint8_t osKernelAddThreads(void (*task0)(void),
                           void (*task1)(void),
                           void (*task2)(void))
{
    __disable_irq();

    /* Link TCBs in round-robin order */
    task_control_block[0].next_task = &task_control_block[1];
    task_control_block[1].next_task = &task_control_block[2];
    task_control_block[2].next_task = &task_control_block[0];

    void (*tasks[3])(void) = { task0, task1, task2 };

    for (int t = 0; t < 3; t++)
    {
        /* Clear stack */
        for (int i = 0; i < NUMBER_OF_ELEMENT; i++)
        {
            TcbStack[t][i] = 0;
        }

        /*
         Stack frame layout expected by your osScheduleLaunch():

         High address
         xPSR
         PC
         LR
         R12
         R3
         R2
         R1
         R0
         R11
         R10
         R9
         R8
         R7
         R6
         R5
         R4   <-- SP starts here
         Low address
        */

        int top = NUMBER_OF_ELEMENT - 1;

        TcbStack[t][top - 0]  = (1U << 24);          // xPSR (Thumb bit)
        TcbStack[t][top - 1]  = (int32_t)tasks[t];   // PC
        TcbStack[t][top - 2]  = 0xFFFFFFFD;          // LR (return using PSP)
        TcbStack[t][top - 3]  = 0;                   // R12
        TcbStack[t][top - 4]  = 0;                   // R3
        TcbStack[t][top - 5]  = 0;                   // R2
        TcbStack[t][top - 6]  = 0;                   // R1
        TcbStack[t][top - 7]  = 0;                   // R0
        TcbStack[t][top - 8]  = 0;                   // R11
        TcbStack[t][top - 9]  = 0;                   // R10
        TcbStack[t][top -10]  = 0;                   // R9
        TcbStack[t][top -11]  = 0;                   // R8
        TcbStack[t][top -12]  = 0;                   // R7
        TcbStack[t][top -13]  = 0;                   // R6
        TcbStack[t][top -14]  = 0;                   // R5
        TcbStack[t][top -15]  = 0;                   // R4

        /* SP points to R4 */
        task_control_block[t].stackpointer =
            &TcbStack[t][top - 15];
    }

    currentptr = &task_control_block[0];

    __enable_irq();

    return 1;
}

void OsKernal_init(void)
{
	MILLI_PRESCALAR = SYS_CLK/1000;
}

//TO LAUNCH THE SYSTICK
void OsKernalLaunch(uint8_t quant){
	//SET PRIORITY
	NVIC_SetPriority(SysTick_IRQn,15);

	//clear the current value
	SysTick->VAL = SYSTICK_CLEAR;

	//load the value we want to interrupt
	SysTick->LOAD = (quant*MILLI_PRESCALAR) - 1;

	//enable the systick / enable the internal clock
	SysTick->CTRL |= SYSTICK_ENABLE|SYSTICK_CLKSOURCE;

	//enable the interrupt
	SysTick->CTRL |= SYSTICK_TICKINT;

	osScheduleLaunch();

}

__attribute__((naked)) void SysTick_Handler(void){

	//Disable the global interrupt
	__asm("CPSID	I");
	//push the r4 - r11 (software register ) to stack
	__asm("PUSH {R4-R11}");
	//load the address of current ptr to r0
	__asm("LDR R0, =currentptr");
	//load the value of current ptr to r1
	__asm("LDR R1, [R0]");
	//store the sp of current task
	__asm("STR	SP,[R1]");
	//load the r1 to next task
	__asm("LDR R1, [R1,#4]");
	//store the r1 value to r0(current_ptr)
	__asm("STR R1, [R0]");
	//store the sp of next task
	__asm("LDR SP,[R1]");
	//restore the r4-r11(software register) to cpu
	__asm("POP {R4-R11}");
	//enable the interrupt
	__asm("CPSIE	I");
	/*Return from exception and restore r0,r1,r2,r3,r12,lr,pc,psr */
	__asm("BX  LR");
}



//One time for load the first task for 1st time
__attribute__((naked)) void osScheduleLaunch(void){

	//Load the address of current_ptr to r0
	__asm("LDR R0, =currentptr");

	//Load the value of address od current_ptr in r1
	__asm("LDR R1, [R0]");

	//Load the value of r1->sp in SP i.e task0->sp
	__asm("LDR SP, [R1]");

	//Restore the r4,r5,r6,r7,r8,r9,r10,r11 from stack -> cpu
	__asm("POP {R4-R11}");

	//Restore the r12 from stack -> cpu
	__asm("POP {R12}");

	//Restore the r0,r1,r2,r3 from stack -> cpu
	__asm("POP {R0-R3}");

	//Skip LR from stack
	__asm("ADD SP, SP,#4");

	//Restore the PC from stack to CPU LR
	__asm("POP {LR}");

	//Skip PSR from stack
	__asm("ADD SP, SP,#4");

	//Enable interrupt
	__asm("CPSIE	I");

	//Return from exception
	__asm("BX	LR");

}




