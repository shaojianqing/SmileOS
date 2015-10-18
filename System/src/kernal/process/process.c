#include "../const/const.h"
#include "../type/type.h"
#include "../gui/sheet.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "process.h"

extern Process *kernelProcess;

void initProcessManagement()
{
	int i=0;
	processManager = (ProcessManager *)PROCESS_TABLE_ADDRESS;
	(*processManager).current = 0;
	(*processManager).running = 1;

	(*processManager).coreProcess.status = STATUS_PROCESS_INIT;
	(*processManager).coreProcess.tssSelector = KERNEL_PROCESS_GDT*8+RPL_0;
	(*processManager).coreProcess.ldtSelector = 0;
	setGlobalDescriptor(KERNEL_PROCESS_GDT, 103, (int)&((*processManager).coreProcess.tss), AR_TSS+DPL_0);	

	for (i=0;i<USER_PROCESS_NUM;i++) {
		(*processManager).processArray[i].status = STATUS_PROCESS_INIT;
		(*processManager).processArray[i].tssSelector = (START_PROCESS_GDT+i)*8+RPL_3;
		(*processManager).processArray[i].ldtSelector = (START_PROCESS_GDT+i+TOTAL_PROCESS_NUM)*8;
		setGlobalDescriptor(START_PROCESS_GDT+i, 103, (int)&((*processManager).processArray[i].tss), AR_TSS+DPL_3);
		setGlobalDescriptor(START_PROCESS_GDT+i+TOTAL_PROCESS_NUM, 63, (int)&((*processManager).processArray[i].ldt), AR_LDT);
	}
}

void prepareKernelProcess()
{
	kernelProcess = &((*processManager).coreProcess);
	loadTr((*kernelProcess).tssSelector);
	registerKernelProcess();	
}

Process *requestProcess()
{	
	int i=0;
	Process *process=null;
	for (i=0;i<USER_PROCESS_NUM;++i) {
		if ((*processManager).processArray[i].status == STATUS_PROCESS_INIT) {
			process = &((*processManager).processArray[i]);
			(*process).status = STATUS_PROCESS_USING;
			(*process).tss.ldtr = (*process).ldtSelector;

			(*process).tss.eip = 0;
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
	ProcessManager *processManager = (ProcessManager *)PROCESS_TABLE_ADDRESS;
	return (*processManager).processList[(*processManager).current];
}

void registerKernelProcess()
{
	(*kernelProcess).priority = 4;
	(*kernelProcess).tss.cr3 = 0x60000;
	(*kernelProcess).status = STATUS_PROCESS_RUNNING;
	(*processManager).processList[(*processManager).current] = kernelProcess;		
}

Process *createProcess(ExecutableFile *file)
{
	if (file != null) {
		return null;	
	}
	return null;
}

Process *addProcess(Process *process)
{	
	if (process != null) {
		ProcessManager *processManager = (ProcessManager *)PROCESS_TABLE_ADDRESS;
		if ((*processManager).running<TOTAL_PROCESS_NUM) {			
			(*processManager).processList[(*processManager).running] = process;
			(*process).status = STATUS_PROCESS_RUNNING;
			(*processManager).running++;
		}		
	}
	return process;
}

Process *removeProcess(Process *process)
{
	if (process != null) {
		ProcessManager *processManager = (ProcessManager *)PROCESS_TABLE_ADDRESS;
		int i=0;
		for(i=0;i<(*processManager).running;++i) {
			if ((*processManager).processList[i]==process) {
				break;			
			}		
		}
		(*processManager).running--;
		if (i<(*processManager).current) {
			(*processManager).current--;		
		}
		if ((*processManager).current>=(*processManager).running) {
			(*processManager).current = 0;		
		}
		(*process).status = STATUS_PROCESS_USING;
		for (;i<(*processManager).running;++i) {
			(*processManager).processList[i] = (*processManager).processList[i + 1];
		}
	}
	return process;
}

Process *startRunProcess(Process *process, int priority)
{
	if (process!=null && (*process).status == STATUS_PROCESS_USING) {
		if (priority>0) {
			(*process).priority = priority;	
		}
		addProcess(process);
	}
	return process;
}

 void startSleepProcess(Process *process)
{
	if (process!=null && (*process).status == STATUS_PROCESS_RUNNING) {
		Process *currentProcess = getCurrentProcess();
		removeProcess(process);
		if (process == currentProcess) {
			currentProcess = getCurrentProcess();
			short currentProcessNum = (*currentProcess).tssSelector;
			switchProcess(0, currentProcessNum);
		}
	}
	return;
}

void startSwitchProcess()
{
	if ((*processManager).currentPriority==0) {
		Process *newProcess, *currentProcess = (*processManager).processList[(*processManager).current];

		(*processManager).current++;
		if ((*processManager).current == (*processManager).running) {
			(*processManager).current = 0;
		}

		newProcess = (*processManager).processList[(*processManager).current];
		if (newProcess != currentProcess) {
			currentProcess = newProcess;
			(*processManager).currentPriority = (*currentProcess).priority;
			short currentProcessNum = (*currentProcess).tssSelector;
			switchProcess(0, currentProcessNum);
		}
	} else {
		(*processManager).currentPriority--;
	}
	return;
}
