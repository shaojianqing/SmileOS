#define AR_TSS32						0x0089

#define MAX_PROCESS_NUM 				1024
#define PROCESS_TABLE_ADDRESS			0x30000

#define STATUS_PROCESS_INIT 			0
#define STATUS_PROCESS_USING 			1
#define STATUS_PROCESS_RUNNING 			2

#define START_PROCESS_GDT 				4

typedef struct Tss
{
	int backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;

	int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;

	int es, cs, ss, ds, fs, gs;

	int ldtr, iomap;
	
} Tss;

typedef struct Process
{
	Tss tss;

	short selector;

	short status;	

} Process;

typedef struct ProcessManager
{
	short running;

	short current;

	Process *processList[MAX_PROCESS_NUM];

	Process processArray[MAX_PROCESS_NUM];

} ProcessManager;

ProcessManager *processManager;

void initTssDescriptor(Tss *tss, int eip, int esp);

Process *initProcessManagement();

Process *requestProcess();

Process *startRunProcess(Process *process);

void startSwitchProcess();
