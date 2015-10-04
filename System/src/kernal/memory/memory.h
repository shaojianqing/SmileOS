#define 	SYS_INFO_BASE		0x21400
#define 	MEM_MANAGE_BASE		0x21800
#define 	SYS_MEM 			1024*1024
#define 	VRAM_MAP 			1024*1024
#define 	MEMORY_NUM 			2000

typedef struct MemoryInfo
{
    u32 addr;

    u32 size;

} MemoryInfo;

typedef struct MemoryManager
{
    u32 num;

    u32 losts;

    u32 lostSize;

    MemoryInfo memoryInfos[MEMORY_NUM];

} MemoryManager;

typedef struct SystemInfo
{
    u32 memorySize;

} SystemInfo;

u32 memorySize();

void initMemoryManagement();

u32 allocMemory(u32 size);

u32 allocMemoryInPage(u32 size);

void freeMemory(u32 addr, u32 size);

void freeMemoryInPage(u32 addr, u32 size);
