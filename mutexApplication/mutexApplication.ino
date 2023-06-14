#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include<string.h>
void task1(void *);
void task2(void *);
TaskHandle_t *task1_h,*task2_h;
SemaphoreHandle_t mutex_h;
void setup()
{
  Serial.begin(9600);
  xTaskCreate(task1, "task1", 500, "task1", 2, task1_h);
  xTaskCreate(task1, "task2", 100, "task2", 2, task2_h);
  mutex_h=xSemaphoreCreateMutex();
}
void loop()
{}
void task1(void * param)
{
  char x[20];
  int y=0;
  for(;;)
  {
    if(xSemaphoreTake(mutex_h, pdMS_TO_TICKS(0))==pdPASS)
    {
      sprintf(x,"%s,%d",(char*)param,y);
      Serial.println(x);
      y++;
     // delay(100);
      xSemaphoreGive(mutex_h);
      taskYIELD();
    }
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}

/*void task2(void * param)
{
  char x[20];
  for(;;)
  {
    xSemaphoreTake(mutex_h, portMAX_DELAY);
    sprintf(x,"%s",(char*)param);
    Serial.println(x);
    xSemaphoreGive(mutex_h);
  }
}*/