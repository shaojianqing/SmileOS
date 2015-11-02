#include "../const/const.h"
#include "../type/type.h"
#include "../memory/memory.h"
#include "../gui/sheet.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "execute.h"
#include "application.h"

void prepareProcessLdt(Process *process, int codeSize, int dataSize, int stackSize);

Application *createApplication(ExecutableFile *executableFile)
{
	if (executableFile != null) {
		ElfProgramHeader *codeHeader = (*executableFile).codeHeader;
		ElfProgramHeader *dataHeader = (*executableFile).dataHeader;
		ElfProgramHeader *stackHeader = (*executableFile).stackHeader;
		
		u32 codeSize = (((*codeHeader).memorySize+0x1000) & 0xFFFFF000);
		u32 dataSize = (((*dataHeader).memorySize+0x1000) & 0xFFFFF000);
		u32 stackSize = APP_STACK_SIZE + APP_TAIL_SIZE;

		u32 totalSize = codeSize + dataSize + stackSize;
		u32 startAddr = allocPage(totalSize);
		u32 startBase = ((startAddr+0x1000) & 0xFFFFF000);
		
		u32 pageNo = startBase/0x1000;

		showIntegerValue(startAddr, 100, 100);

		showIntegerValue(startBase, 100, 160);

		showIntegerValue(pageNo, 100, 220);
		
		Application *application = (Application *)alloc(sizeof(Application));
		(*application).startBase = startBase;
		(*application).startAddr = startAddr;
		(*application).totalSize = totalSize;
		Process *process = requestProcess();
		prepareProcessLdt(process, codeSize, dataSize, stackSize);
		(*application).process = process;

		return application;			
	}
}

void startApplication(Application *application)
{
	if (application != null) {
			
	}
}

void prepareProcessLdt(Process *process, int codeSize, int dataSize, int stackSize)
{
	if (process != null) {
		setLocalDescriptor((int)&(*process).ldt, CODE_SELECTOR, codeSize, 0x00000000, DA_C);
		setLocalDescriptor((int)&(*process).ldt, DATA_SELECTOR, dataSize, 0x00000000, DA_DRW);
		setLocalDescriptor((int)&(*process).ldt, STACK_SELECTOR, stackSize, 0x00000000, DA_DRWA);
	}
}
