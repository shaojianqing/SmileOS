#define APP_STACK_SIZE 			0x10000

#define APP_TAIL_SIZE 			0x1000

#define CODE_SELECTOR			0x01

#define DATA_SELECTOR			0x02

#define STACK_SELECTOR			0x03


typedef struct Application
{
	int startAddr;

	int startBase;

	int totalSize;

	Process *process;

} Application;

Application *createApplication(ExecutableFile *executableFile);

void startApplication(Application *application);
