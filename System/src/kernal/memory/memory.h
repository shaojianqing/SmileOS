#define 	SYS_INFO_BASE		0x20400
#define 	MEM_MANAGE_BASE		0x21800
#define 	SYS_MEM 			1024*1024
#define 	VRAM_MAP 			1024*1024
#define 	SYS_HEAP_BASE		1024*1024*2
#define		SYS_HEAP_SIZE		1024*1024*2
#define		SYS_PAGE_BASE		1024*1024*4

#define 	MEM_INFO_NUM 		600
#define		MEM_PAGE_BASE		0x61000
#define		MEM_PAGE_NUM		0x4000

#define		STATUS_UNDEFIN		0x00
#define		STATUS_UNALLOC		0x01
#define		STATUS_ALLOCED		0x02

typedef struct MemoryInfo MemoryInfo;

typedef struct View View;

typedef struct MemoryInfo
{
	u8 status;

    u32 addr;

    u32 size;

	MemoryInfo *prev;

	MemoryInfo *next;

} MemoryInfo;

typedef struct MemoryManager
{
	u32 totalNum;
	
	MemoryInfo *firstMemoryInfo;

	MemoryInfo *lastMemoryInfo;

	MemoryInfo *memoryInfos[MEM_INFO_NUM];

    MemoryInfo memoryInfoList[MEM_INFO_NUM];

} MemoryManager;

typedef struct SystemInfo
{
    u32 memorySize;

} SystemInfo;

void initMemoryManagement();

u32 alloc(u32 size);

u32 allocPage(u32 size);

void release(u32 addr);

void releasePage(u32 addr, u32 size);
