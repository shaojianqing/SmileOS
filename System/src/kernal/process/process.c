#include "../const/const.h"
#include "../type/type.h"
#include "process.h"

extern Process *kernelProcess;

void initTssDescriptor(Tss *tss, int eip, int esp) {
	(*tss).eip = eip;	
	(*tss).ldtr = 0;
	(*tss).iomap = 0x40000000;
	(*tss).eflags = 0x00000202;
	(*tss).eax = 0;
	(*tss).ecx = 0;
	(*tss).edx = 0;
	(*tss).ebx = 0;
	(*tss).esp = esp;
	(*tss).ebp = 0;
	(*tss).esi = 0;
	(*tss).edi = 0;
	(*tss).es = 2*8;
	(*tss).cs = 1*8;
	(*tss).ss = 2*8;
	(*tss).ds = 2*8;
	(*tss).fs = 2*8;
	(*tss).gs = 2*8;
}

void initProcessManagement()
{
	int i=0;
	processManager = (ProcessManager *)PROCESS_TABLE_ADDRESS;
	for (i=0;i<MAX_PROCESS_NUM;++i) {
		(*processManager).processArray[i].status = STATUS_PROCESS_INIT;
		(*processManager).processArray[i].selector = (START_PROCESS_GDT+i)*8;
		setGlobalDescriptor(START_PROCESS_GDT+i, 103, (int)&((*processManager).processArray[i].tss), AR_TSS32);
	}
	
	for (i=0;i<MAX_LEVEL_NUMBER;++i) {
		(*processManager).levelList[i].running = 0;
		(*processManager).levelList[i].current = 0;
	}
}

void prepareKernelProcess() 
{
	kernelProcess = requestProcess();
	(*kernelProcess).status = STATUS_PROCESS_RUNNING;
	(*kernelProcess).level = 0;
	addProcess(kernelProcess);
	switchProcessLevel();			
	loadTr((*kernelProcess).selector);
}

Process *requestProcess()
{	
	int i=0;
	Process *process=null;
	for (i=0;i<MAX_PROCESS_NUM;++i) {
		if ((*processManager).processArray[i].status == STATUS_PROCESS_INIT) {
			process = &((*processManager).processArray[i]);
			(*process).status = STATUS_PROCESS_USING;
			
			(*process).tss.eip = 0;	
			(*process).tss.ldtr = 0;
			(*process).tss.iomap = 0x40000000;
			(*process).tss.eflags = 0x00000202;
			(*process).tss.eax = 0;
			(*process).tss.ecx = 0;
			(*process).tss.edx = 0;
			(*process).tss.ebx = 0;
			(*process).tss.esp = 0;
			(*process).tss.ebp = 0;
			(*process).tss.esi = 0;
			(*process).tss.edi = 0;
			(*process).tss.es = 0;
			(*process).tss.cs = 0;
			(*process).tss.ss = 0;
			(*process).tss.ds = 0;
			(*process).tss.fs = 0;
			(*process).tss.gs = 0;

			return process;
		}
	}
	return null;
}

Process *getCurrentProcess()
{
	ProcessLevel *processLevel = &((*processManager).levelList[(*processManager).currentLevel]);
	if (processLevel != null) {
		return (*processLevel).processList[(*processLevel).current];	
	}
	return null;
}

Process *addProcess(Process *process)
{	
	if (process != null) {
		ProcessLevel *processLevel = &((*processManager).levelList[(*process).level]);
		if ((*processLevel).running<MAX_PROCESS_LEVEL) {
			(*processLevel).processList[(*processLevel).running] = process;
			(*processLevel).running++;
			(*process).status = STATUS_PROCESS_RUNNING;
		}		
	}
	return process;
}

Process *removeProcess(Process *process)
{
	if (process != null) {
		int i=0;
		ProcessLevel *processLevel = &((*processManager).levelList[(*process).level]);
		for(i=0;i<(*processLevel).running;++i) {
			if ((*processLevel).processList[i]==process) {
				break;			
			}		
		}
		(*processLevel).running--;
		if (i<(*processLevel).current) {
			(*processLevel).current--;		
		}

		if ((*processLevel).current>=(*processLevel).running) {
			(*processLevel).current = 0;		
		}
		
		(*process).status = STATUS_PROCESS_USING;
		for (;i<(*processLevel).running;++i) {
			(*processLevel).processList[i] = (*processLevel).processList[i + 1];
		}		
	}
	return process;
}

void switchProcessLevel() 
{
	int i=0;
	for (i=0;i<MAX_LEVEL_NUMBER;++i) {
		if ((*processManager).levelList[i].running>0) {
			break;		
		}
	}
	(*processManager).currentLevel = i;
	(*processManager).isChangeLevel = FALSE;
}

Process *startRunProcess(Process *process, int level, int priority)
{
	if (process!=null && (*process).status == STATUS_PROCESS_USING) {
		if (level<0) {
			level = (*process).level;	
		}

		if (priority>0) {
			(*process).priority = priority;	
		}

		if ((*process).status == STATUS_PROCESS_RUNNING && (*process).level != level) {
			removeProcess(process);
		}

		if ((*process).status == STATUS_PROCESS_USING) {
			(*process).level = level;
			addProcess(process);
		}
		(*processManager).isChangeLevel = TRUE;
	}
	return process;
}

 void startSleepProcess(Process *process)
{
	if (process!=null && (*process).status == STATUS_PROCESS_RUNNING) {
		Process *currentProcess = getCurrentProcess();
		removeProcess(currentProcess);
		if (process == currentProcess) {
			switchProcessLevel();
			currentProcess = getCurrentProcess();
			short currentProcessNum = (*currentProcess).selector;
			switchProcess(0, currentProcessNum);
		}
	}
	return;
}

void startSwitchProcess()
{
	if ((*processManager).currentPriority==0) {
		ProcessLevel *processLevel = &((*processManager).levelList[(*processManager).currentLevel]);
		Process *newProcess, *currentProcess = (*processLevel).processList[(*processLevel).current];

		(*processLevel).current++;
		if ((*processLevel).current == (*processLevel).running) {
			(*processLevel).current = 0;
		}

		if ((*processManager).isChangeLevel == TRUE) {
			switchProcessLevel();
			processLevel = &((*processManager).levelList[(*processManager).currentLevel]);
		}

		newProcess = (*processLevel).processList[(*processLevel).current];
		if (newProcess != currentProcess) {
			currentProcess = newProcess;
			(*processManager).currentPriority = (*currentProcess).priority;
			short currentProcessNum = (*currentProcess).selector;
			switchProcess(0, currentProcessNum);
		}
	} else {
		(*processManager).currentPriority--;
	}
	return;
}
