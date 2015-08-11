#define AR_TSS32						0x0089

#define MAX_PROCESS_NUM 				1000
#define PROCESS_TABLE_ADDRESS			0x30000

#define STATUS_PROCESS_INIT 			0
#define STATUS_PROCESS_USING 			1
#define STATUS_PROCESS_RUNNING 			2

#define START_PROCESS_GDT 				4

#define MAX_PROCESS_LEVEL				100

#define MAX_LEVEL_NUMBER				10

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

	int priority;

	int level;

	Sheet *mainWindow;

} Process;

typedef struct ProcessLevel
{
	int running;

	int current;

	Process *processList[MAX_PROCESS_LEVEL];

} ProcessLevel;

typedef struct ProcessManager
{
	int currentLevel;

	bool isChangeLevel;

	int currentPriority;

	ProcessLevel levelList[MAX_LEVEL_NUMBER];

	Process processArray[MAX_PROCESS_NUM];

} ProcessManager;

ProcessManager *processManager;

void initTssDescriptor(Tss *tss, int eip, int esp);

void initProcessManagement();

void prepareKernelProcess();

void prepareIdleProcess();

Process *requestProcess();

Process *getCurrentProcess();

Process *addProcess(Process *process);

Process *removeProcess(Process *process);

Process *startRunProcess(Process *process, int level, int priority);

void startSleepProcess(Process *process);

void switchProcessLevel();

void startSwitchProcess();
