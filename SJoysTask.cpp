#include "SJoysTask.h"

void vJoystickTask( void * xParameter) {
  SJoysTaskParams* xParams = (SJoysTaskParams*)xParameter;

  TickType_t xLastWakeTime;
  const TickType_t xPeriod = pdMS_TO_TICKS( SJOYS_TASK_FREQ );
  xLastWakeTime = xTaskGetTickCount();
  for ( ;; )  {
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    SJoysInfo info = xParams->SJoys->read(0,100);
    //SJoysInfo info = xParams->SJoys->read();
    if (xQueueSend(xParams->xQueue, &info, portMAX_DELAY) != pdPASS) {

    }
  }
}
