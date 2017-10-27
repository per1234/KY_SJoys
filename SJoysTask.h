#ifndef SJoysTask_h
#define SJoysTask_h

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "KY_SJoys.h"

/* Keyes SJoystick Task parameters */
#define SJOYS_TASK_CODE     vJoystickTask
#define SJOYS_STACK_DEPTH   128
#define SJOYS_TASK_NAME     ( signed portCHAR * )"vSJoysTask"
#define SJOYS_TASK_PRIORITY tskIDLE_PRIORITY + 1
#define SJOYS_TASK_FREQ     100 /* [milliseconds] */

/* The following structure is used to pass parameters into a task function. */
typedef struct SJoysTaskParams
{
  KY_SJoys* SJoys;          // Pointer to the Keyes Sjoystick instance.
  QueueHandle_t xQueue;     // Reference to a communication queue.
} SJoysTaskParams;

/* Keyes SJoystick task function header. */
void vJoystickTask( void * xParameter);

#endif
