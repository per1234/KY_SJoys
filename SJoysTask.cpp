#include "SJoysTask.h"

/* Keyes SJoystick task function implementation.
   This task run at a frequency given by SJOYS_TASK_FREQ.
   See also SJoysTask.h */
void vJoystickTask( void * xParameter) {
  /* Extract parameters passed to this function when SJoystick Task have been created */
  SJoysTaskParams* xParams = (SJoysTaskParams*)xParameter;

  TickType_t xLastWakeTime;
  /* The pdMS_TO_TICKS macro is used to convert milliseconds into ticks */
  const TickType_t xPeriod = pdMS_TO_TICKS( SJOYS_TASK_FREQ );
  /* The xLastWakeTime variable needs to be initialized with the current tick
     count. Note that this is the only time the variable is written to explicitly.
     After this assignment, xLastWakeTime is updated automatically internally within
     vTaskDelayUntil(). */
  xLastWakeTime = xTaskGetTickCount();
  /* Enter the loop that defines the SJoys task behavior. */
  for ( ;; )  {
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    /* Perform the periodic actions here. */
    SJoysInfo info = xParams->SJoys->read(0, 100);
    if (xQueueSend(xParams->xQueue, &info, portMAX_DELAY) != pdPASS) {

    }
  }
}
