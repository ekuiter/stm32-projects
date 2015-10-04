#include <includes.h>

static OS_STK StartTaskStk[START_TASK_STK_SIZE];

extern void AppInit(void);

static void TaskStart(void *p_arg);

void GPIO_Configuration(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE); 
  GPIO_Config(GPIOC, GPIO_Pin_13, GPIO_Mode_IN_FLOATING);
  GPIO_Config(GPIOB, GPIO_Pin_2, GPIO_Mode_IN_FLOATING);
}

s32 main(void) {
	CPU_IntDis();
  OSInit();
  OSTaskCreateExt((void (*)(void*)) TaskStart, 0, &StartTaskStk[START_TASK_STK_SIZE - 1], START_TASK_PRIO,
    START_TASK_PRIO, &StartTaskStk[0], START_TASK_STK_SIZE, 0, OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK);
	OSStart();
	return 0;
}

static void TaskStart(void *p_arg) {
	GPIO_Configuration();
  OS_CPU_SysTickInit();
  AppInit();
  while (1)
    OSTimeDlyHMSM(0, 1, 0, 0);
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) { 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  while (1);
}
#endif
