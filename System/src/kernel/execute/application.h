/* 
 * The config infomation of the elf application file.
 */
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

/* 
 * The Application data struture represents one application image in the memory.
 * It is usually constructed from the ExecutableFile data and is used to create
 * and config the process data.
 */
typedef struct Application
{
	int startAddr;

	int totalSize;

	Process *process;

} Application;

/* 
 * Create the application data based on the executableFile.
 *
 * Parameters:
 * 	executableFile: the executableFile to create the application.
 * Return:
 *		the application pointer that is used to create one process image.
 */
Application *createApplication(ExecutableFile *executableFile);

/* 
 * Start the application, so that the OS can run and schedule the process
 * created by the application.
 *
 * Parameters:
 * 	application: the application to be started.
 * Return:
 *		no return value.
 */
void startApplication(Application *application);
