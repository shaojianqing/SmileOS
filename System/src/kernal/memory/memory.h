#define 	SYS_INFO_BASE		0x21400
#define 	MEM_MANAGE_BASE		0x21800
#define 	SYS_MEM 			1024*1024
#define 	VRAM_MAP 			1024*1024
#define 	SYS_HEAP_BASE		1024*1024*2
#define		SYS_HEAP_SIZE		1024*1024*2
#define		SYS_PAGE_BASE		1024*1024*4

#define 	MEMORY_NUM 			2000
#define		MEM_PAGE_BASE		0x61000
#define		MEM_PAGE_NUM		0x4000

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

    MemoryInfo memoryInfo[MEMORY_NUM];

} MemoryManager;

typedef struct SystemInfo
{
    u32 memorySize;

} SystemInfo;

void initMemoryManagement();

u32 alloc(u32 size);

u32 allocPage(u32 size);

void release(u32 addr, u32 size);

void releasePage(u32 addr, u32 size);
