
#define MAX_TIMER_NUM			512
#define STATUS_TIMER_UNUSE		0
#define STATUS_TIMER_ALLOC		1
#define STATUS_TIMER_USING		2

typedef struct Timer
{	
	u64 timeout;

	u8 status;

	u8 data;

	struct Timer *next;

	QueueBuffer *queue;
} Timer;

typedef struct TimerManager
{	
	u64 time;

	u64 latest;

	Timer *currentTimer;

	Timer timerList[MAX_TIMER_NUM];
} TimerManager;

void intHandler20();

void initTimerManagement();

Timer* requestTimer(u64 timeout, u8 data, QueueBuffer *queue);

void releaseTimer(Timer *timer);

u64 getTime();
