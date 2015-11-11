#include "../const/const.h"
#include "../type/type.h"
#include "../memory/memory.h"
#include "../gui/sheet.h"
#include "../gui/test.h"
#include "execute.h"

ExecutableFile* loadExecuteFromStorage(u32 sector)
{
	ExecutableFile *executeFile = null;
	u8 *headBuffer = (u8 *)allocPage(SECTOR_SIZE);
	if (headBuffer!=null) {
    	readHardDisk(sector, headBuffer, SECTOR_SIZE);
    	ElfFileHeader *header = (ElfFileHeader *)headBuffer;
		u32 bufferSize = (*header).shOffset+(*header).shentSize*(*header).shNum;
		//release((int)headBuffer, SECTOR_SIZE);		
	
		executeFile = (ExecutableFile *)allocPage(sizeof(ExecutableFile));
		if (executeFile!=null) {
			(*executeFile).executeSize = bufferSize;
			(*executeFile).executeBuffer = (u8 *)allocPage(bufferSize);
			readHardDisk(sector, (*executeFile).executeBuffer, bufferSize);
			(*executeFile).header = (ElfFileHeader *)(*executeFile).executeBuffer;
			ElfFileHeader *header = (*executeFile).header;
			ElfProgramHeader *programHeader = (ElfProgramHeader *)((int)header + (*header).phOffset);
			int i=0;
			for (i=0;i<(*header).phNum;++i) {
				ElfProgramHeader *program = programHeader+i;
				if ((*program).flags==FLAG_ELF_CODE) {
					(*executeFile).codeHeader = program;
				} else if ((*program).flags==FLAG_ELF_DATA) {
					(*executeFile).dataHeader = program;
				} else if ((*program).flags==FLAG_ELF_STACK) {
					(*executeFile).stackHeader = program;
				}		
			}
		}
	}
	
    return executeFile;
}
