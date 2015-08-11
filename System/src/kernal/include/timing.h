
#define MAX_TIMER_NUM			512
#define STATUS_TIMER_UNUSE		0
#define STATUS_TIMER_ALLOC		1
#define STATUS_TIMER_USING		2

typedef struct Timer Timer;

struct Timer
{	
	u64 timeout;

	u8 status;

	Timer *next;

	void (*onTimer)();
};

typedef struct TimerManager
{	
	u64 time;

	u64 latest;

	Timer *currentTimer;

	Timer timerList[MAX_TIMER_NUM];
} TimerManager;

void intHandler20();

void initTimerManagement();

Timer* requestTimer(u64 timeout, void (*onTimer)());

Timer* requestCurrentTimer(u64 timeout, void (*onTimer)());

void releaseTimer(Timer *timer);

u64 getTime();
