/* 
 * The system memory allocation layout constants.
 */
#define 	SYS_INFO_BASE		0x21400
#define 	MEM_MANAGE_BASE		0x22800
#define 	SYS_MEM 			1024*1024
#define 	VRAM_MAP 			1024*1024
#define 	SYS_HEAP_BASE		1024*1024*2
#define		SYS_HEAP_SIZE		1024*1024*2
#define		SYS_PAGE_BASE		1024*1024*4

/* 
 * The memoryInfo number and page count constants.
 */
#define 	MEM_INFO_NUM 		600
#define		MEM_PAGE_BASE		0x61000
#define		MEM_PAGE_NUM		0x4000

/* 
 * The memoryInfo status constants.
 */
#define		STATUS_UNDEFIN		0x00
#define		STATUS_UNALLOC		0x01
#define		STATUS_ALLOCED		0x02

typedef struct MemoryInfo MemoryInfo;

typedef struct MemoryManager MemoryManager;

/* 
 * The MemoryInfo data structure, it represents one memory fragment in total memory,
 * and it has the address and size field, as welll as the status field which marks the
 * memory fragment being alloced or unalloced.There are also another fields prev and next
 * pointer because the memoryInfo is organized and managed in the form of linked list.
 */
struct MemoryInfo
{
	u8 status;

    u32 addr;

    u32 size;

	MemoryInfo *prev;

	MemoryInfo *next;

};

/* 
 * The MemoryManager data structure, it keep record of the total memory size,
 * the memoryInfo list, so that it can record and manage the allocation of the
 * system memory.
 */
struct MemoryManager
{
	u32 totalNum;
	
	MemoryInfo *firstMemoryInfo;

	MemoryInfo *lastMemoryInfo;

	MemoryInfo *memoryInfos[MEM_INFO_NUM];

    MemoryInfo memoryInfoList[MEM_INFO_NUM];

};

/* 
 * Initialize the MemoryManager instance, including initialize the memoryInfo
 * list and setting the first and last memoryInfo and the relative status, linked
 * pointers of them. 
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initMemoryManagement();

/* 
 * Allocate some few size of memory (less than 1k)
 *
 * Parameters:
 * 		size: the size of the memory to be allocated.
 * Return:
 *		the address of allocated memory fragment.
 */
u32 alloc(u32 size);

/* 
 * Allocate some relative large size of memory (larger than 1k)
 *
 * Parameters:
 * 		size: the size of the memory to be allocated.
 * Return:
 *		the address of allocated memory fragment.
 */
u32 allocPage(u32 size);

/* 
 * Free some few size of memory (less than 1k)
 *
 * Parameters:
 * 		addr: the memory address to be freed.
 * Return:
 *		no return value.
 */
void release(u32 addr);

/* 
 * Free some relative large size of memory (larger than 1k)
 *
 * Parameters:
 * 		addr: the memory address to be freed.
 * Return:
 *		no return value.
 */
void releasePage(u32 addr, u32 size);

/* 
 * Copy the data from one address to another address in memory.
 *
 * Parameters:
 * 		src: the source address of the data in the memory.
 *	   dest: the destination address of the data in the memory.
 *	  count: the total size of the data to be copied.
 * Return:
 *		no return value.
 */
void memoryCopy(void *src, void *dest, u32 count);
