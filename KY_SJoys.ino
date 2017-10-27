#include "SJoysTask.h"

uint8_t SJoysPin[SJOY_PIN_NBR] = {0, 1, 8};
KY_SJoys joystick(SJoysPin[VRX_PIN],
                  SJoysPin[VRY_PIN],
                  SJoysPin[SW_PIN],
                  EPSILON );

QueueHandle_t xQueue;
static void vPrintTask( void * );

void setup() {
  // put your setup code here, to run once:
  joystick.initialize();
  Serial.begin(9600);

  xQueue = xQueueCreate(10, sizeof(SJoysInfo));
  if (xQueue == NULL) {
    /* Queue could not be created. */
    return;
  }
  SJoysTaskParams xParameter = { &joystick, xQueue };

  xTaskCreate(
    vJoystickTask,
    SJOYS_TASK_NAME,
    SJOYS_STACK_DEPTH,
    (void*)&xParameter,
    SJOYS_TASK_PRIORITY,
    NULL );

  xTaskCreate(
    vPrintTask,
    ( signed portCHAR * )
    "vPrintTask",
    128,
    NULL,
    tskIDLE_PRIORITY + 1,
    NULL );

  vTaskStartScheduler();
}

static void vPrintTask( void * ) {
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = pdMS_TO_TICKS( SJOYS_TASK_FREQ );
  xLastWakeTime = xTaskGetTickCount();
  for ( ;; )  {
    vTaskDelayUntil( &xLastWakeTime, xPeriod );
    SJoysInfo info;
    if (xQueueReceive(xQueue, &info, portMAX_DELAY) != pdPASS) {

    }
    Serial.print("X: ");    Serial.print(info.VRx);
    Serial.print(", Y: ");  Serial.print(info.VRy);
    Serial.print(", B: ");  Serial.println(info.SW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
