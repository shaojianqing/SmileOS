#define APP_STACK_SIZE 			0x10000

#define APP_HEAP_SIZE 			0x100000

#define APP_PAGE_DIR_SIZE 		0x1000

#define APP_PAGE_SIZE			0x10000

#define APP_TAIL_SIZE 			0x1000

#define APP_START_ADDR			0x0000

#define CODE_SELECTOR			0x00

#define DATA_SELECTOR			0x01

#define STACK_SELECTOR			0x02

#define APP_PAGE_ATTR			0x07

#define PAGE_DIR_SIZE			0x400000

#define PAGE_SIZE				0x1000


typedef struct Application
{
	int startAddr;

	int totalSize;

	Process *process;

} Application;

Application *createApplication(ExecutableFile *executableFile);

void startApplication(Application *application);
