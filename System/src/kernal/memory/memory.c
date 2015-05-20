#define SYS_MEM 1024*1024
#define VRAM_MAP 1024*768*2
#define MEMORY_NUM 2000

typedef struct MemoryInfo
{

    unsigned int addr;

    unsigned int size;
} MemoryInfo;

typedef struct MemoryManager
{

    unsigned int num;

    unsigned int losts;

    unsigned int lostSize;

    MemoryInfo memoryInfos[MEMORY_NUM];

} MemoryManager;

typedef struct SystemInfo
{

    unsigned int memorySize;

} SystemInfo;

void initMemoryManagement()
{
    SystemInfo *systemInfo = (SystemInfo *)0x21400;
    (*systemInfo).memorySize*=1024;
    (*systemInfo).memorySize-=(SYS_MEM+VRAM_MAP);

    MemoryManager *memoryManager = (MemoryManager *)0x21800;
    (*memoryManager).num = 1;
    (*memoryManager).losts = 0;
    (*memoryManager).lostSize = 0;
    MemoryInfo *memoryInfo = (MemoryInfo *)(*memoryManager).memoryInfos;
    (*memoryInfo).addr = SYS_MEM+VRAM_MAP;
    (*memoryInfo).size = (*systemInfo).memorySize;
}

unsigned int memorySize()
{
    MemoryManager *memoryManager = (MemoryManager *)0x21800;
    if ((*memoryManager).num>0)
    {
        unsigned int memorySize = 0;
        int i=0;
        for (i=0; i<(*memoryManager).num; ++i)
        {
            MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfos+i);
            memorySize+=(*memoryInfo).size;
        }
        return memorySize;
    }
    return 0;
}

unsigned int allocMemory(unsigned int size)
{
    if (size>0)
    {
        int address;
        MemoryManager *memoryManager = (MemoryManager *)0x21800;
        if ((*memoryManager).num>0)
        {
            int i=0;
            for (i=0; i<(*memoryManager).num; ++i)
            {
                MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfos+i);
                if ((*memoryInfo).size>=size)
                {
                    address = (*memoryInfo).addr;
                    (*memoryInfo).addr+=size;
                    (*memoryInfo).size-=size;
                    return address;
                }
            }
        }
    }
    return 0;
}

unsigned int allocMemoryInPage(unsigned int size)
{
    if (size>0)
    {
        size = (size+0xfff)&0xfffff000;
        return allocMemory(size);
    }
    return 0;
}

void freeMemory(unsigned int addr, unsigned int size)
{
    if (size>0 && addr>=SYS_MEM+VRAM_MAP)
    {

        Color color;
        color.red = 255;
        color.green = 255;
        color.blue = 255;

        MemoryManager *memoryManager = (MemoryManager *)0x21800;
        unsigned int i=0, j=0, index=0;
        for (i=0; i<(*memoryManager).num; ++i)
        {
            MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfos+i);
            if ((*memoryInfo).addr>addr)
            {
                index = i;
                break;
            }
        }

        if (index>0)
        {
            MemoryInfo *prevInfo = (MemoryInfo *)((*memoryManager).memoryInfos+index-1);
            if ((*prevInfo).addr+(*prevInfo).size == addr)
            {
                (*prevInfo).size+=size;

                if (index<(*memoryManager).num)
                {
                    MemoryInfo *nextInfo = (MemoryInfo *)((*memoryManager).memoryInfos+index);
                    if (addr+size==(*nextInfo).addr)
                    {
                        (*prevInfo).size+=(*nextInfo).size;
                        (*memoryManager).num--;
                        for (i=0; i<(*memoryManager).num; ++i)
                        {
                            *((*memoryManager).memoryInfos+i) = *((*memoryManager).memoryInfos+i+1);
                        }
                    }
                }
            }
            return;
        }

        if (index<(*memoryManager).num)
        {
            MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfos+index);
            if (addr+size==(*memoryInfo).addr)
            {
                (*memoryInfo).addr = addr;
                (*memoryInfo).size += size;
            }
            return;
        }

        if ((*memoryManager).num<MEMORY_NUM)
        {
            for (j=(*memoryManager).num; j>index; ++j)
            {
                *((*memoryManager).memoryInfos+j) = *((*memoryManager).memoryInfos+j-1);
            }
            (*memoryManager).num++;
            MemoryInfo *memoryInfo = (MemoryInfo *)((*memoryManager).memoryInfos+index);
            (*memoryInfo).addr = addr;
            (*memoryInfo).size = size;
            return;
        }
        (*memoryManager).losts++;
        (*memoryManager).lostSize+=size;
    }
    return;
}

void freeMemoryInPage(unsigned int addr, unsigned int size)
{
    size=(size+0xfff)&0xfffff000;
    freeMemoryInPage(addr, size);
}

