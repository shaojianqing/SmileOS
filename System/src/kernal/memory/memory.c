#include "../const/const.h"
#include "../type/type.h"
#include "memory.h"

void initMemoryManagement()
{
    MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
    (*memoryManager).num = 1;
    (*memoryManager).losts = 0;
    (*memoryManager).lostSize = 0;
    MemoryInfo *memoryInfo = (MemoryInfo *)(*memoryManager).memoryInfo;
    (*memoryInfo).addr = SYS_HEAP_BASE;
    (*memoryInfo).size = SYS_HEAP_SIZE;
}

u32 alloc(u32 size)
{
    if (size>0) {
        u32 address;
        MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
        if ((*memoryManager).num>0) {
            u32 i=0;
            for (i=0; i<(*memoryManager).num; ++i) {
                MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfo+i);
                if ((*memoryInfo).size>=size) {
                    address = (*memoryInfo).addr;
                    (*memoryInfo).addr+=size;
                    (*memoryInfo).size-=size;
                    return address;
                }
            }
        }
    }
    return null;
}

u32 allocPage(u32 size)
{
    if (size>0) {
		int *page = (int *)MEM_PAGE_BASE;
		int start = (SYS_PAGE_BASE/0x1000);
        size = ((size+0xfff)&0xfffff000);
		int num = (size/0x1000), p = 0, i = 0, j = 0, total = 0;
		
		while(i<num && total<MEM_PAGE_NUM) {
			p = *(page+start+i);
			if ((p&0xE00)==0) {
				++i;
			} else {
				page+=(i+1);
				i=0;		
			}
			++total;
		}
		if (total<MEM_PAGE_NUM) {
			for (j=0;j<num;++j) {
				p = *(page+start+j);
				p = (p|0xE00);
				*(page+start+j) = p;
			}
			p = *(page+start);
			u32 address = (p&0xFFFFF000);
			return address;
		}				
    }
	return null;
}

void release(u32 addr, u32 size)
{
    if (size>0 && addr>=SYS_HEAP_BASE) {
        MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
        u32 i=0, j=0, index=0;
        for (i=0; i<(*memoryManager).num; ++i) {
            MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfo+i);
            if ((*memoryInfo).addr>addr) {
                index = i;
                break;
            }
        }

        if (index>0) {
            MemoryInfo *prevInfo = (MemoryInfo *)((*memoryManager).memoryInfo+index-1);
            if ((*prevInfo).addr+(*prevInfo).size == addr) {
                (*prevInfo).size+=size;

                if (index<(*memoryManager).num) {
                    MemoryInfo *nextInfo = (MemoryInfo *)((*memoryManager).memoryInfo+index);
                    if (addr+size==(*nextInfo).addr) {
                        (*prevInfo).size+=(*nextInfo).size;
                        (*memoryManager).num--;
                        for (i=0; i<(*memoryManager).num; ++i) {
                            *((*memoryManager).memoryInfo+i) = *((*memoryManager).memoryInfo+i+1);
                        }
                    }
                }
            }
            return;
        }

        if (index<(*memoryManager).num) {
            MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfo+index);
            if (addr+size==(*memoryInfo).addr) {
                (*memoryInfo).addr = addr;
                (*memoryInfo).size += size;
            }
            return;
        }

        if ((*memoryManager).num<MEMORY_NUM) {
            for (j=(*memoryManager).num; j>index; ++j) {
                *((*memoryManager).memoryInfo+j) = *((*memoryManager).memoryInfo+j-1);
            }
            (*memoryManager).num++;
            MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfo+index);
            (*memoryInfo).addr = addr;
            (*memoryInfo).size = size;
            return;
        }
        (*memoryManager).losts++;
        (*memoryManager).lostSize+=size;
    }
}

void releasePage(u32 addr, u32 size)
{
	if (size>0) {
		size = ((size+0xfff)&0xfffff000);
		int *page = (int *)MEM_PAGE_BASE;
		int num = size/0x1000, p = 0, i = 0, j = 0, total = 0;
		addr = (addr&0xFFFFF000);
		int start = addr/0x1000;

		while(i<num) {
			p = *(page+start+i);
			if ((p&0xE00)>0) {
				p = (p&0xfffff1ff);
				*(page+start+i) = p;
				++i;
			}
		}			
	}
}

