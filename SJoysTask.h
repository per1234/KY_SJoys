#ifndef SJoysTask_h
#define SJoysTask_h

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include "KY_SJoys.h"

#define SJOYS_STACK_DEPTH   128
#define SJOYS_TASK_NAME     ( signed portCHAR * )"vSJoysTask"
#define SJOYS_TASK_PRIORITY tskIDLE_PRIORITY + 1
#define SJOYS_TASK_FREQ     100 /* [milliseconds] */

typedef struct SJoysTaskParams
{
  KY_SJoys* SJoys;
  QueueHandle_t xQueue;
} SJoysTaskParams;

void vJoystickTask( void * xParameter);

#endif
