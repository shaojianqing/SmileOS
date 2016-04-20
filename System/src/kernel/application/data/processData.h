#define TYPE_PROCESS_SYSS 0
#define TYPE_PROCESS_USER 1

#define SIGN_PROCESS_RUNNING 0
#define SIGN_PROCESS_BLOCKED 1
#define SIGN_PROCESS_READY 2

typedef struct ProcessData ProcessData;

typedef struct ProcessData
{
	int pId;

    char *name;

	int wordCount;

	char type;

	char status;
	
	int priority;

} ProcessData;
