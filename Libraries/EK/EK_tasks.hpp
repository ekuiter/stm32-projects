#ifndef  __EK_TASKS_HPP
#define  __EK_TASKS_HPP

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <uCOS-II/Source/ucos_ii.h>
#include <uCOS-II/Ports/ARM-Cortex-M3/RealView/os_cpu.h>
#include <uC-CPU/ARM-Cortex-M3/RealView/cpu.h>

#define HIGHEST_PRIO 3

typedef void (*simpleRunFunc_t)(void);

extern simpleRunFunc_t PriorityTable[];

using std::vector;

extern vector<void*> Tasks;

template <int StackSize = sizeof(OS_STK), typename runFunc_t = simpleRunFunc_t, typename arg_t = int>
class Task {
	private:
		const int StackSizeInternal; // holds StackSize in bytes for use with ReportStackUsages() (because void* is stored in Tasks)
	  const char* TaskName;
		const int Priority;
	  bool Started;
	  bool Suspended;
	  runFunc_t RunFunc; // do NOT change position!
	  OS_STK Stack[StackSize / sizeof(OS_STK)]; // do NOT change position!
	
	  int PriorityFromTable(void* priorityTable, runFunc_t rf) {
			int taskCount;
		  for (taskCount = 0; PriorityTable[taskCount] != NULL; taskCount++);
			simpleRunFunc_t* start = PriorityTable;
			simpleRunFunc_t* end = PriorityTable + taskCount;
			simpleRunFunc_t* position = std::find(start, end, (simpleRunFunc_t) rf);
			if (position != end)
				return HIGHEST_PRIO + (position - start);
			else
				return -1;
		}
			
  public:
		Task(const char* tn, runFunc_t rf): StackSizeInternal(StackSize / sizeof(OS_STK) * sizeof(OS_STK)), TaskName(tn),
    Priority(PriorityFromTable(PriorityTable, rf)), Started(false), Suspended(false), RunFunc(rf) {}

		~Task() {
		  Delete();
		}
			
	  void Run(arg_t arg) {
			if (!Started) {
				Started = true;
				Tasks.push_back(this);
		    //OSTaskCreate(reinterpret_cast<void (*)(void*)>(RunFunc), (void*) arg, &Stack[StackSizeInternal / sizeof(OS_STK) - 1], Priority); // for use without stack checking
		    OSTaskCreateExt(reinterpret_cast<void (*)(void*)>(RunFunc), (void*) arg, &Stack[StackSizeInternal / sizeof(OS_STK) - 1],
					Priority, Priority, Stack, StackSizeInternal / sizeof(OS_STK), 0, OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK);
			} else
			  Resume();
		}
		
		void Run(void) {
			Run((arg_t) 0);
		}
		
		void Suspend(void) {
			if (Started && !Suspended) {
				Suspended = true;
		    OSTaskSuspend(Priority);
			}
		}
		
		void Resume(void) {
			if (Started && Suspended) {
				Suspended = false;
		    OSTaskResume(Priority);
			}
		}
		
		void Delete(void) {
		  if (Started) {
				Started = false;
				Suspended = false;
				for (vector<void*>::iterator it = Tasks.begin(); it != Tasks.end(); ++it)
					if (*it == this) {
						Tasks.erase(it);
						break;
					}
				OSTaskDel(Priority);
			}
		}
		
		bool Running(void) {
		  return Started && !Suspended;
		}
		
		const char* GetTaskName(void) {
		  return TaskName;
		}
		
		uint32_t GetStackUsage(void) {
			OS_STK_DATA stackData;
		  OSTaskStkChk(Priority, &stackData);
			return stackData.OSUsed * sizeof(OS_STK);
		}
		
		void ReportStackUsage() {
			uint32_t stackUsage = GetStackUsage();
			int percentage = stackUsage * 100 / StackSizeInternal;
		  printf("Stack: %*d / %*d bytes (%*d%%) %s stack is ", 5, stackUsage, 5, StackSizeInternal, 3, percentage, TaskName);
			if (percentage >= 100)
				printf("exhausted!");
			else if (percentage >= 90)
				printf("almost exhausted!");
			else
				printf("fine.");
			printf("\r\n");
		}
		
		static void ReportStackUsages() {
		  for (int i = 0; i < Tasks.size(); i++) {
				Task<>* task = reinterpret_cast<Task<>*>(Tasks[i]);
			  task->ReportStackUsage();
			}
		}
};

#endif
