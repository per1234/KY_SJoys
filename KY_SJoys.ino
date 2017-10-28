#include "SJoysTask.h"
#include <semphr.h>

/* used to store the Arduino pins connected to the Keyes SJoytick pins */
uint8_t SJoysPin[SJOY_PIN_NBR] = {0, 1, 2};
/* call the KY_SJoys object constructor */
KY_SJoys joystick(SJoysPin[VRX_PIN],
                  SJoysPin[VRY_PIN],
                  SJoysPin[SW_PIN],
                  EPSILON );

TaskHandle_t xPrintTaskHandle;  // Reference to the X and Y Axes state Printing task.
TaskHandle_t xSJoysTaskHandle;  // Reference to the X and Y Axes state measurement task.

QueueHandle_t xQueue;           // Reference to PrintTask and SJoysTask communication queue.

void vPrintTask( void * );      // PrintTask function header.
void JoystikSwTask(void *);     // SJoystick Switch button listener(Task) function header.

/* A semaphore is going to be used to guard the Serial shared resource */
SemaphoreHandle_t xSemaphore = xSemaphoreCreateMutex();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  joystick.initialize();

  xQueue = xQueueCreate(10, sizeof(SJoysInfo));
  if (xQueue == NULL) {
    /* Queue could not be created. */
    return;
  }
  SJoysTaskParams xParameter = { &joystick, xQueue };

  xTaskCreate(
    SJOYS_TASK_CODE,
    SJOYS_TASK_NAME,
    SJOYS_STACK_DEPTH,
    (void*)&xParameter,
    SJOYS_TASK_PRIORITY,
    xSJoysTaskHandle );

  xTaskCreate(
    JoystikSwTask,
    ( signed portCHAR * )
    "JoystikSwTask",
    128,
    NULL,
    tskIDLE_PRIORITY + 1,
    NULL );

  xTaskCreate(
    vPrintTask,
    ( signed portCHAR * )
    "vPrintTask",
    128,
    NULL,
    tskIDLE_PRIORITY + 1,
    xPrintTaskHandle );

  vTaskStartScheduler();
}
void JoystikSwTask(void *) {
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = pdMS_TO_TICKS( SJOYS_TASK_FREQ );
  xLastWakeTime = xTaskGetTickCount();
  for (short index = 0 ;; index = ((index + 1) % SW_QUEUE_LEN) )  {
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    joystick.SW_status[index] = joystick.readSW();
    if ( xSemaphoreTake( xSemaphore, 10 ) == pdTRUE ) {
      Serial.print("index: ");  Serial.print(index);
      Serial.print(", B: ");  Serial.println(joystick.SW_status[index]);
      xSemaphoreGive( xSemaphore );
    }

    if ((joystick.SW_status[index] - (joystick.SW_status[(index - 1) % SW_QUEUE_LEN])) == -1) {
      joystick.OnOff = !joystick.OnOff;
      if ( xSemaphoreTake( xSemaphore, 10 ) == pdTRUE ) {
        Serial.println("Joystick Switch Event");
        if (joystick.OnOff == true) {
          Serial.println("joystick.OnOff == true");
        } else {
          Serial.println("joystick.OnOff == false");
        }
        xSemaphoreGive( xSemaphore );
      }
    }
  }
}

void vPrintTask( void * xParameter) {
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = pdMS_TO_TICKS( SJOYS_TASK_FREQ );
  xLastWakeTime = xTaskGetTickCount();
  for ( ;; )  {
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    SJoysInfo info;
    if (xQueueReceive(xQueue, &info, portMAX_DELAY) != pdPASS) {

    }
    if ( xSemaphoreTake( xSemaphore, 10 ) == pdTRUE ) {
      Serial.print("X: ");    Serial.print(info.VRx);
      Serial.print(", Y: ");  Serial.println(info.VRy);
      xSemaphoreGive( xSemaphore );
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
