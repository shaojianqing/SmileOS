#include "../const/const.h"
#include "../type/type.h"
#include "process.h"

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

Process *initProcessManagement()
{
	int i=0;
	Process *process;
	processManager = (ProcessManager *)PROCESS_TABLE_ADDRESS;
	for (i=0;i<MAX_PROCESS_NUM;++i) {
		(*processManager).processArray[i].status = STATUS_PROCESS_INIT;
		(*processManager).processArray[i].selector = (START_PROCESS_GDT+i)*8;
		setGlobalDescriptor(START_PROCESS_GDT+i, 103, (int)&((*processManager).processArray[i].tss), AR_TSS32);
	}
	process = requestProcess();
	(*process).status = STATUS_PROCESS_RUNNING;
	(*processManager).running = 1;
	(*processManager).current = 0;
	(*processManager).processList[0] = process;
	loadTr((*process).selector);
	return process;
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

Process *startRunProcess(Process *process)
{
	if (process!=null) {
		(*process).status = STATUS_PROCESS_RUNNING;
		(*processManager).processList[(*processManager).running] = process;
		(*processManager).running++;
	}
	return process;
}

void startSwitchProcess()
{
	if ((*processManager).running>=2) {
		(*processManager).current++;
		if ((*processManager).current==(*processManager).running) {
			(*processManager).current=0;	
		}
		short currentProcessNum = (*(*processManager).processList[(*processManager).current]).selector;
		switchProcess(0, currentProcessNum);	
	}
	return;
}
