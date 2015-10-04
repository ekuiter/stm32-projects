#include <includes.h>
#include <EK.hpp>
#include <vector>

static void RunTouchPanelTask(void);
static void RunGUITask(void);
static void RunBlinkTask(void);
static Task<64> TouchPanelTask(3, RunTouchPanelTask);
static Task<512> GUITask(4, RunGUITask);
static Task<64> BlinkTask(OS_LOWEST_PRIO - 3, RunBlinkTask);

static GPIO_Pin PB0("PB0", GPIO_Mode_Out_PP);
static GPIO_Pin PB1("PB1", GPIO_Mode_Out_PP);

static USART Serial(USART1, 115200);

static char buf[10];

void AppInit(void) {
	TouchPanelTask.Run();
	GUITask.Run();
	BlinkTask.Run();
	
	printf("Gib was ein:\r\n");
	Serial.ReadLn(buf, 10);
	printf("Du hast eingegeben: %s", buf);
}	

extern "C" void MainTask(void);	

static void RunGUITask(void) {   
	GUI_Touch_Config();
	while (1)
		MainTask();
}

static void RunTouchPanelTask(void) {   
	while (1) {
	 GUI_TOUCH_Exec();
	 OSTimeDlyHMSM(0, 0, 0, 20);
	}
}

static void RunBlinkTask(void) {                 
	while (1) {  
		OSTimeDlyHMSM(0, 0, 0, 500);
		PB0.On(); PB1.Off();
		OSTimeDlyHMSM(0, 0, 0, 500);
		PB0.Off(); PB1.On();
	}
}
