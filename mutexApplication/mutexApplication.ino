
#include<stdlib.h>
#include<string.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
typedef struct data_h
{
  int num;
  char name[20];
}data_t;
void task1(data_t *);
void task2(data_t *);
TaskHandle_t *task1_h,*task2_h;
SemaphoreHandle_t mutex_h;
void setup()
{
  Serial.begin(9600);
  data_t *data1=(data_t*)malloc(sizeof(data_t));
  strcpy(data1->name,"task1");
  data1->num=1000;
  xTaskCreate(task1, "task1", 500, data1, 2, task1_h);
  data_t *data2=(data_t*)malloc(sizeof(data_t));
  strcpy(data2->name,"task2");
  data2->num=1000;
  xTaskCreate(task1, "task2", 500, &data2, 2, task2_h);
  mutex_h=xSemaphoreCreateMutex();
}
void loop()
{}
void task1(data_t *param)
{
  char x[20];
  int y=0;
  for(;;)
  {
    if(xSemaphoreTake(mutex_h, pdMS_TO_TICKS(0))==pdPASS)
    {
      sprintf(x,"%s,%d",(char*)param->name,y);
      Serial.println(x);
      y++;
      delay(100);
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