#include <includes.h>

static OS_STK StartTaskStk[START_TASK_STK_SIZE];

extern void AppInit(void);

static void StartTask(void *p_arg) {
  OS_CPU_SysTickInit();
  AppInit();
  while (1)
    OSTimeDlyHMSM(0, 1, 0, 0);
}

s32 main(void) {
	CPU_IntDis();
  OSInit();
  OSTaskCreateExt((void (*)(void*)) StartTask, 0, &StartTaskStk[START_TASK_STK_SIZE - 1], START_TASK_PRIO,
    START_TASK_PRIO, &StartTaskStk[0], START_TASK_STK_SIZE, 0, OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK);
	OSStart();
	return 0;
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) { 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  while (1);
}
#endif
