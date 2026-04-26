# Tiny RTOS for STM32F401RE (Bare Metal)

A lightweight custom Real-Time Operating System (RTOS) built from scratch on STM32F401RE using **Bare Metal programming (without HAL)**.

This project was developed to understand how RTOS kernels work internally by implementing core features manually instead of relying on existing frameworks.

## Features

* Task Creation and Management
* Task Control Block (TCB) implementation
* Separate stack space for each task
* Round Robin Scheduler
* SysTick-based periodic scheduling
* Context Switching using ARM Cortex-M registers
* First task launch using preloaded stack frame
* Bare Metal register-level programming

## Concepts Covered

* ARM Cortex-M stack behavior
* CPU Registers (PC, LR, SP, xPSR, R0-R12)
* Saving and restoring task context
* Scheduler design
* Task switching mechanism
* Embedded memory management basics

## Hardware Used

* STM32F401RE
* ARM Cortex-M4 Core

## Why This Project?

Most developers use RTOS libraries like FreeRTOS through APIs.
This project focuses on learning **what happens inside the kernel**:

* How tasks are stored
* How stacks are initialized
* How scheduling works
* How context switching happens

## Future Improvements

* Priority-based scheduling
* Delay / Sleep APIs
* Semaphores & Mutexes
* Dynamic task creation
* Inter-task communication
* Tickless idle mode

## Learning Outcome

This project provided hands-on experience with low-level embedded systems programming and a deeper understanding of RTOS internals.

## Author

Developed by [Your Name]

## Tags

RTOS, STM32, Bare Metal, Embedded Systems, ARM Cortex-M4, Scheduler, Context Switching, Firmware Development
