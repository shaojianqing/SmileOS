#include "../const/const.h"
#include "../type/type.h"
#include "../memory/memory.h"
#include "../gui/sheet.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "execute.h"
#include "application.h"

void prepareProcessLdt(Process *process, u32 codeSize, u32 dataSize, u32 stackSize);

void prepareProcessTss(Process *process, u32 startAddr, u32 codeSize, u32 dataSize, u32 stackSize);

void prepareProcessPage(u32 startAddr, u32 totalSize, u32 codeSize, u32 dataSize, u32 stackSize, u32 heapSize, u32 pageDirSize, u32 pageSize);

Application *createApplication(ExecutableFile *executableFile)
{
	if (executableFile != null) {
		ElfProgramHeader *codeHeader = (*executableFile).codeHeader;
		ElfProgramHeader *dataHeader = (*executableFile).dataHeader;
		ElfProgramHeader *stackHeader = (*executableFile).stackHeader;
		
		u32 codeSize = (((*codeHeader).memorySize+0xFFF) & 0xFFFFF000);
		u32 dataSize = (((*dataHeader).memorySize+0xFFF) & 0xFFFFF000);
		u32 stackSize = APP_STACK_SIZE + APP_TAIL_SIZE;
		u32 pageDirSize = APP_PAGE_DIR_SIZE;
		u32 pageSize = APP_PAGE_SIZE;
		u32 heapSize = APP_HEAP_SIZE;		

		u32 totalSize = codeSize + dataSize + stackSize + heapSize + pageDirSize + pageSize;
		u32 startAddr = allocPage(totalSize);
		
		Application *application = (Application *)alloc(sizeof(Application));
		(*application).startAddr = startAddr;
		(*application).totalSize = totalSize;

		u8 *codeDest = (u8 *)(startAddr + pageDirSize + pageSize);
		u8 *dataDest = (u8 *)(startAddr + pageDirSize + pageSize + codeSize);

		u8 *codeSource = (u8 *)((*executableFile).executeBuffer + (*codeHeader).offset);
		u8 *dataSource = (u8 *)((*executableFile).executeBuffer + (*dataHeader).offset);

		memoryCopy(codeSource, codeDest, codeSize);
		memoryCopy(dataSource, dataDest, dataSize);

		Process *process = requestProcess();
		prepareProcessPage(startAddr, totalSize, codeSize, dataSize, stackSize, heapSize, pageDirSize, pageSize);
		prepareProcessLdt(process, codeSize, dataSize, stackSize);
		prepareProcessTss(process, startAddr, codeSize, dataSize, stackSize);
		(*application).process = process;	

		return application;			
	}
}

void startApplication(Application *application)
{
	if (application != null) {
		startRunProcess((*application).process, 4);
	}
}

void prepareProcessPage(u32 startAddr, u32 totalSize, u32 codeSize, u32 dataSize, u32 stackSize, u32 heapSize, u32 pageDirSize, u32 pageSize)
{
	u32 i=0;
	u32 pageNum = totalSize/PAGE_DIR_SIZE;
	if (totalSize%PAGE_DIR_SIZE==0) {
		pageNum = totalSize/PAGE_DIR_SIZE;
	} else {
		pageNum = totalSize/PAGE_DIR_SIZE+1;
	}
	u32 *pdtb = (u32 *)startAddr;	
	for (i=0;i<pageNum;++i) {
		*(pdtb+i) = startAddr + pageDirSize + i*PAGE_SIZE + APP_PAGE_ATTR;
	}	
	
	u32 *pageBase = (u32 *)(startAddr + pageDirSize);
	for (i=0;i<1024;++i) {
		*(pageBase+i) = startAddr + pageDirSize + pageSize + i*PAGE_SIZE + APP_PAGE_ATTR;
	}
}

void prepareProcessLdt(Process *process, u32 codeSize, u32 dataSize, u32 stackSize)
{
	if (process != null) {
		setLocalDescriptor((u32)&(*process).ldt, CODE_SELECTOR, 0xFFFFF, 0x00000000, DA_C|DA_32_4K);
		setLocalDescriptor((u32)&(*process).ldt, DATA_SELECTOR, 0xFFFFF, 0x00000000, DA_DRW|DA_32_4K);
		setLocalDescriptor((u32)&(*process).ldt, STACK_SELECTOR, stackSize, 0x00000000, DA_DRWA|DA_32_4K);
	}
}

void prepareProcessTss(Process *process, u32 startAddr, u32 codeSize, u32 dataSize, u32 stackSize) 
{
	if (process != null) {
		(*process).tss.esp = (startAddr + codeSize + dataSize + stackSize);
		(*process).tss.eip = APP_START_ADDR;		
		(*process).tss.cs = 0 * 8 + 4;		
		(*process).tss.ds = 1 * 8 + 4;
		(*process).tss.es = 1 * 8 + 4;
		(*process).tss.fs = 1 * 8 + 4;
		(*process).tss.gs = 1 * 8 + 4;
		(*process).tss.ss = 2 * 8 + 4;
		(*process).tss.cr3 = startAddr;
	}
}

