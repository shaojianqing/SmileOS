#define AR_TSS						    0x0089
#define AR_LDT							0x0082

#define DPL_0							0x00
#define DPL_3							0x60

#define RPL_0							0x00
#define RPL_3							0x03

#define TOTAL_PROCESS_NUM				1000
#define USER_PROCESS_NUM 				TOTAL_PROCESS_NUM-1
#define PROCESS_TABLE_ADDRESS			0x31000

#define STATUS_PROCESS_INIT 			0
#define STATUS_PROCESS_USING 			1
#define STATUS_PROCESS_RUNNING 			2

#define KERNEL_PROCESS_GDT 				1024
#define START_PROCESS_GDT 				KERNEL_PROCESS_GDT+1

#define MAX_LDT_NUM						4

#define PROCESS_NAME_LENGTH				32

/* 
 * The Task Status Segment data structure.The most fundamental
 * data structure representing the process context and register
 * field.This data structure can be recognized and accessed by
 * the CPU directly.
 */
typedef struct Tss
{
	int backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;

	int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;

	int es, cs, ss, ds, fs, gs;

	int ldtr, iomap;
	
} Tss;

/* 
 * The Local Descriptor Table data structure.Representing the
 * local descriptor table of one particiular process.In this OS,
 * I set that every process has at most 4 local segments.
 */
typedef struct Ldt
{
	LocalDescriptor descriptor[MAX_LDT_NUM];
	
} Ldt;

/* 
 * The Process data structure in this OS.It just represents the process
 * running in this OS and contains all kinds of resources that one 
 * process needs to possess, including Tss, Ldt and relative selector, 
 * status, priority and so on.
 */
typedef struct Process
{
	Tss tss;

	Ldt ldt;

	short tssSelector;

	short ldtSelector;

	short status;

	int priority;

	u32 index;

	Sheet *mainWindow;

	char *name;

} Process;

/* 
 * The Process Manager data structure that manages process, maintains
 * process list, keeps record of current process property and so on.
 * There is only one instance of Process Manager in this OS.
 */
typedef struct ProcessManager
{
	int running;

	int current;

	int currentPriority;

	Process coreProcess;

	Process *processList[TOTAL_PROCESS_NUM];

	Process processArray[USER_PROCESS_NUM];

} ProcessManager;

/* 
 * The singleton instance of ProcessManager.
 */
ProcessManager *processManager;

/* 
 * Initialize the ProcessManager instance, including building the 
 * initial process list, setting default values, preparing the kernel
 * process and intalling the segments into the GDT table.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initProcessManagement();

/* 
 * Prepare and registe the kernel process and intall it into the GDT table 
 * and tr register,thus the kernel process can be controlled and scheduled
 * by the ProcessManager. 
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void prepareKernelProcess();

/* 
 * Set the kernel process priority, status and cr3 register, so that the
 * kernel can be controled and scheduled by the ProcessManager.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void registerKernelProcess();

/* 
 * Request one new process from the process list.The process is to be initialized
 * added into the ready process queue waiting for ProcessManager to be controlled 
 * and scheduled.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		Process pointer.
 */
Process *requestProcess();

/* 
 * Get the current running process.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		Process pointer.
 */
Process *getCurrentProcess();

/* 
 * Add the process into ready process queue, so that the ProcessManager can control
 * and schedule the process.
 *
 * Parameters:
 * 		process: Process pointer to be added into the ready queue.
 * Return:
 *		process: Process pointer to be added into the ready queue.
 */
Process *addProcess(Process *process);

/* 
 * Remove the process from ready process queue, so that the status of the process is
 * changed to be blocked status.
 *
 * Parameters:
 * 		process: Process pointer to be removed from the ready queue.
 * Return:
 *		process: Process pointer to be removed from the ready queue.
 */
Process *removeProcess(Process *process);

/* 
 * Start the process with the priority if it is the turn of the process and the time 
 * slice is ready. 
 *
 * Parameters:
 * 		process: Process pointer to be started.
 *		priority: Running priority of the process.
 * Return:
 *		process: Process pointer to be started.
 */
Process *startRunProcess(Process *process, int priority);

/* 
 * Switch the process status and make the status be sleep status. 
 *
 * Parameters:
 * 		process: Process pointer to be sleep.
 * Return:
 *		no return value.
 */
void startSleepProcess(Process *process);

/* 
 * Start to switch process to the next process, if the time interrupt occurs and the 
 * time slice of current process is end.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		Process pointer.
 */
void startSwitchProcess();

/* 
 * Switch to kernel process directly and immediately where keyboard or mouse interrupt
 * occurs, so that the user input can be responsed quickly and fluently.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		Process pointer.
 */
void switchKernelProcess();
