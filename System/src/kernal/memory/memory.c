#include "../const/const.h"
#include "../type/type.h"
#include "../algorithm/algorithm.h"
#include "memory.h"

void initMemoryManagement()
{
    MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
    MemoryInfo *memoryInfo = (MemoryInfo *)(*memoryManager).memoryInfoList;
	(*memoryManager).firstMemoryInfo = memoryInfo;
	(*memoryManager).lastMemoryInfo = memoryInfo;
	(*memoryManager).totalNum = 0;
	(*memoryInfo).status = STATUS_UNALLOC;
    (*memoryInfo).addr = SYS_HEAP_BASE;
    (*memoryInfo).size = SYS_HEAP_SIZE;
	(*memoryInfo).next = null;
	(*memoryInfo).prev = null;
}

MemoryInfo* getOriginMemoryInfo()
{
	MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
	int i=0;
	for (i=0;i<MEM_INFO_NUM;++i) {
		MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfoList+i);
		if ((*memoryInfo).status==STATUS_UNDEFIN) {
			return memoryInfo;
		}	
	}
	return null;
}

bool isAddrLargeThan(Object *object1, Object *object2) 
{
	MemoryInfo *memoryInfo1 = (MemoryInfo *)object1;
	MemoryInfo *memoryInfo2 = (MemoryInfo *)object2;
	if (memoryInfo1!=null && memoryInfo2!=null) {
		if ((*memoryInfo1).status>(*memoryInfo2).status) {
			return TRUE;		
		} else if ((*memoryInfo1).status==(*memoryInfo2).status){
			if ((*memoryInfo1).addr>(*memoryInfo2).addr) {
				return TRUE;			
			}		
		}
	}
	return FALSE;
}

bool isSizeLargeThan(Object *object1, Object *object2) 
{
	MemoryInfo *memoryInfo1 = (MemoryInfo *)object1;
	MemoryInfo *memoryInfo2 = (MemoryInfo *)object2;
	if (memoryInfo1!=null && memoryInfo2!=null) {
		if ((*memoryInfo1).status>(*memoryInfo2).status) {
			return TRUE;		
		} else if ((*memoryInfo1).status==(*memoryInfo2).status){
			if ((*memoryInfo1).size>(*memoryInfo2).size) {
				return TRUE;			
			}		
		}
	}
	return FALSE;
}

u32 alloc(u32 size)
{
    if (size>0) {
		size = ((size+0xf)&0xfffffff0);
        MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
		MemoryInfo *currentMemoryInfo = (*memoryManager).firstMemoryInfo;
		MemoryInfo *allocedMemoryInfo = null;
	
		u32 i=0;
		while(currentMemoryInfo!=null) {
			(*memoryManager).memoryInfos[i] = currentMemoryInfo;
			currentMemoryInfo = (*currentMemoryInfo).next;
			++i;
		}
		(*memoryManager).totalNum = i;
		u32 totalNum = (*memoryManager).totalNum;
		for (i=0;i<totalNum;++i) {
			MemoryInfo *memoryInfo = (*memoryManager).memoryInfos[i];
			if ((*memoryInfo).status == STATUS_UNALLOC) {
				if ((*memoryInfo).size>=size) {
					if ((*memoryInfo).size==size) {
						(*memoryInfo).status = STATUS_ALLOCED;
						allocedMemoryInfo = memoryInfo;
					} else if ((*memoryInfo).size>size) {
						if (totalNum<MEM_INFO_NUM) {
							allocedMemoryInfo = getOriginMemoryInfo();
							(*allocedMemoryInfo).size = size;
							(*allocedMemoryInfo).addr = (*memoryInfo).addr;
							(*allocedMemoryInfo).status = STATUS_ALLOCED;
							(*memoryManager).memoryInfos[totalNum] = allocedMemoryInfo;
							(*memoryInfo).size-=size;
							(*memoryInfo).addr+=size;
							totalNum++;
						}					
					}
					break;				
				}			
			}		
		}
		(*memoryManager).totalNum = totalNum;
		sort((Object **)(*memoryManager).memoryInfos, totalNum, isSizeLargeThan);
		if (totalNum>=1) {
			for (i=0;i<totalNum;++i) {
				MemoryInfo *memoryInfo = (*memoryManager).memoryInfos[i];
				(*memoryInfo).prev = null;
				(*memoryInfo).next = null;						
			}

			for (i=0;i<totalNum-1;++i) {
				MemoryInfo *memoryInfo1 = (*memoryManager).memoryInfos[i];
				MemoryInfo *memoryInfo2 = (*memoryManager).memoryInfos[i+1];
				if (memoryInfo1!=memoryInfo2) {
					(*memoryInfo1).next = memoryInfo2;
					(*memoryInfo2).prev = memoryInfo1;	
				}
			}
			(*memoryManager).firstMemoryInfo = (*memoryManager).memoryInfos[0];
			(*memoryManager).lastMemoryInfo = (*memoryManager).memoryInfos[totalNum-1];
		}
		return (*allocedMemoryInfo).addr;
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

void release(u32 addr)
{
	if (addr!=null) {
		MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
		MemoryInfo *currentMemoryInfo = (*memoryManager).firstMemoryInfo;
		MemoryInfo *memoryInfo = (*memoryManager).lastMemoryInfo;
		while (TRUE) {
			if (memoryInfo==null) {
				break;			
			} else if ((*memoryInfo).addr==addr) {
				break;			
			} else {
				memoryInfo = (*memoryInfo).prev;
			}
		}
		if (memoryInfo!=null) {
			(*memoryInfo).status = STATUS_UNALLOC;
			u32 i=0, j=0, totalNum=0;
			while(currentMemoryInfo!=null) {
				(*memoryManager).memoryInfos[i] = currentMemoryInfo;
				currentMemoryInfo = (*currentMemoryInfo).next;
				++i;
			}
			(*memoryManager).totalNum = i;
			totalNum = (*memoryManager).totalNum;
			if (totalNum>1) {
				sort((Object **)(*memoryManager).memoryInfos, totalNum, isAddrLargeThan);
				i=0;
				while(i<totalNum-1) {
					MemoryInfo *memoryInfo1 = (*memoryManager).memoryInfos[i];
					MemoryInfo *memoryInfo2 = (*memoryManager).memoryInfos[i+1];
					if ((*memoryInfo1).status==STATUS_UNALLOC && (*memoryInfo2).status==STATUS_UNALLOC) {
						u32 top = (*memoryInfo1).addr + (*memoryInfo1).size;
						if (top==(*memoryInfo2).addr) {
							(*memoryInfo1).size += (*memoryInfo2).size;
							(*memoryInfo2).status = STATUS_UNDEFIN;
							(*memoryInfo2).prev = null;
		 					(*memoryInfo2).next = null;
							for (j=i+1;j<totalNum-1;++j) {
								(*memoryManager).memoryInfos[j] = (*memoryManager).memoryInfos[j+1];					
							}
							totalNum--;
						} else {
							++i;						
						}
					} else {
						++i;					
					}				
				}
				(*memoryManager).totalNum = totalNum;
				sort((Object **)(*memoryManager).memoryInfos, totalNum, isSizeLargeThan);
				if (totalNum>=1) {
					for (i=0;i<totalNum;++i) {
						MemoryInfo *memoryInfo = (*memoryManager).memoryInfos[i];
						(*memoryInfo).prev = null;
						(*memoryInfo).next = null;						
					}
	
					for (i=0;i<totalNum-1;++i) {
						MemoryInfo *memoryInfo1 = (*memoryManager).memoryInfos[i];
						MemoryInfo *memoryInfo2 = (*memoryManager).memoryInfos[i+1];
						if (memoryInfo1!=memoryInfo2) {
							(*memoryInfo1).next = memoryInfo2;
							(*memoryInfo2).prev = memoryInfo1;	
						}
					}
					(*memoryManager).firstMemoryInfo = (*memoryManager).memoryInfos[0];
					(*memoryManager).lastMemoryInfo = (*memoryManager).memoryInfos[totalNum-1];
				}
			}						
		}
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

