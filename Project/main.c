/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/*
 * main() creates all the demo application tasks, then starts the scheduler.
 * The web documentation provides more details of the standard demo application
 * tasks, which provide no particular functionality but do provide a good
 * example of how to use the FreeRTOS API.
 *
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Check" task - This only executes every five seconds but has a high priority
 * to ensure it gets processor time.  Its main function is to check that all the
 * standard demo tasks are still operational.  While no errors have been
 * discovered the check task will print out "OK" and the current simulated tick
 * time.  If an error is discovered in the execution of a task then the check
 * task will print out an appropriate error message.
 *
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h" /* RTOS firmware */
#include "task.h"     /* Task */
#include "timers.h"
//#include "queue.h"
/* Examples */
#define ERTS2_TASKMANAGEMENT

/* --------------------------------------------- */
#ifdef ERTS2_TASKMANAGEMENT
// you need make your task visible @TODO
// example
// void vTask1();

void vTask(void *);

void vTaskManager(void *);

void vTask1(void *);
void vTask2(void *);
void vTask3(void *);
void vTask4(void *);

void vSporadicTask(void *);

#endif

void vApplicationIdleHook(void);

int main(void)
{
#ifdef ERTS2_TASKMANAGEMENT
    /* Creating Four Task with different Priorities and Delay*/
    // search and find xTaskCreate how it is work
    //	xTaskCreate( vTask1, "Task 1", 1000, NULL, 1, NULL );

    xTaskCreate(vTask1, "Task 1", 10000, NULL, 4, NULL);
    xTaskCreate(vTask2, "Task 2", 10000, NULL, 3, NULL);
    xTaskCreate(vTask3, "Task 3", 10000, NULL, 2, NULL);
    xTaskCreate(vTask4, "Task 4", 10000, NULL, 1, NULL);

    xTaskCreate(vSporadicTask, "Sporadic Task", 10000, NULL, 8, NULL);

    xTaskCreate(vTaskManager, "Task Manager", 10000, NULL, 7, NULL);

#endif

    vTaskStartScheduler();
    return 0;
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName)
{
    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
    exit(-1);
}

#ifdef ERTS2_TASKMANAGEMENT
// define your Task here @TODO

void vTask(void *p)
{
    int delay = (int)p;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        printf("Hi. delay is %d\n", delay);

        // vTaskDelay(pdMS_TO_TICKS(delay));
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(delay));
    }
}

void vTaskManager(void *p)
{
    int period = 2000;
    TaskHandle_t task1_handler = xTaskGetHandle("Task 1");

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        vTaskSuspend(task1_handler);
        printf("Task1 suspended.\n");
        vTaskDelay(pdMS_TO_TICKS(500));
        vTaskResume(task1_handler);
        printf("Task1 resumed.\n");

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));
    }
}

void vTask1(void *p)
{
    int c_time = 250, period = 5000, deadline = 2500;
    TaskStatus_t xTaskDetails;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        // start of execution time
        printf("Task 1 started at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        TickType_t begin = xTaskDetails.ulRunTimeCounter;
        while ((xTaskDetails.ulRunTimeCounter - begin) < pdMS_TO_TICKS(c_time / 10))
            vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        printf("Task 1 ended at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        // end of execution time

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));
    }
}

void vTask2(void *p)
{
    int c_time = 500, period = 3000, deadline = 3000;
    TaskStatus_t xTaskDetails;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        // start of execution time
        printf("Task 2 started at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        TickType_t begin = xTaskDetails.ulRunTimeCounter;
        while ((xTaskDetails.ulRunTimeCounter - begin) < pdMS_TO_TICKS(c_time / 10))
            vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        printf("Task 2 ended at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        // end of execution time

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));
    }
}

void vTask3(void *p)
{
    int c_time = 750, period = 2000, deadline = 3500;
    TaskStatus_t xTaskDetails;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        // start of execution time
        printf("Task 3 started at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        TickType_t begin = xTaskDetails.ulRunTimeCounter;
        while ((xTaskDetails.ulRunTimeCounter - begin) < pdMS_TO_TICKS(c_time / 10))
            vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        printf("Task 3 ended at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        // end of execution time

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));
    }
}

void vTask4(void *p)
{
    int c_time = 1000, period = 4000, deadline = 5000;
    TaskStatus_t xTaskDetails;

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        // start of execution time
        printf("Task 4 started at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        TickType_t begin = xTaskDetails.ulRunTimeCounter;
        while ((xTaskDetails.ulRunTimeCounter - begin) < pdMS_TO_TICKS(c_time / 10))
            vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        printf("Task 4 ended at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        // end of execution time

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(period));
    }
}

void vSporadicTask(void *p)
{
    int c_time = 100, min_period = 3000;
    TaskStatus_t xTaskDetails;
    srand(43);

    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        // start of execution time
        printf("Sporadic Task started at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        TickType_t begin = xTaskDetails.ulRunTimeCounter;
        while ((xTaskDetails.ulRunTimeCounter - begin) < pdMS_TO_TICKS(c_time / 10))
            vTaskGetInfo(NULL, &xTaskDetails, pdFALSE, eInvalid);
        printf("Sporadic Task ended at %dms\n", xTaskGetTickCount() / portTICK_RATE_MS);
        // end of execution time

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(min_period + (rand() % 4096)));
    }
}

#endif
/* CH3_TASKMANAGEMENT ends */

void vApplicationIdleHook(void)
{
    // printf("Idle\r\n");
}
/*-----------------------------------------------------------*/
