
/* 
 * The total timer number constants.
 */
#define MAX_TIMER_NUM			512

/* 
 * The timer status constants when running and switching.
 */
#define STATUS_TIMER_UNUSE		0
#define STATUS_TIMER_ALLOC		1
#define STATUS_TIMER_USING		2

typedef struct Timer Timer;

/* 
 * The Timer data structure, it represents one timer that may be requested to provide
 * timing signals for the kernel or user process. It is organized in the form of linked
 * list and has the "onTimer" as the callback function that is to notify the caller.
 */
struct Timer
{	
	u64 timeout;

	u8 status;

	Timer *next;

	void (*onTimer)();
};

/* 
 * The TimerManager data structure, it is used to organize and manage the timer list,
 * current latest timer and total time period. With this data structure, the caller 
 * can easily request one timer and get the timing service from it.
 */
typedef struct TimerManager
{	
	u64 time;

	u64 latest;

	Timer *currentTimer;

	Timer timerList[MAX_TIMER_NUM];

} TimerManager;

/* 
 * Initialize the timing data and reset the timer status, and then travse the timer
 * linked list to find the latest timer, finally trigger the timer's callback function
 * and reorganize the timer linked list when timing interrupt is triggered.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void intHandler20();

/* 
 * Initialize the timerManager data and initialize the timer list, set the defalut value.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initTimerManagement();

/* 
 * Request one timer from the timer list by passing the parameter timeout and one callback
 * function.
 *
 * Parameters:
 * 		timeout: the timeout time of the timer.
		onTimer: the callback function of the client which is called when time is out.
 * Return:
 *		Timer pointer.
 */
Timer* requestTimer(u64 timeout, void (*onTimer)());

/* 
 * Request the current timer from the timer list by passing the parameter timeout and one callback
 * function.
 *
 * Parameters:
 * 		timeout: the timeout time of the timer.
		onTimer: the callback function of the client which is called when time is out.
 * Return:
 *		Timer pointer.
 */
Timer* requestCurrentTimer(u64 timeout, void (*onTimer)());

/* 
 * Release and restore the timer, so that the timer can be reused in the next time.
 *
 * Parameters:
 * 		timer: the timer to be release and restored.
 * Return:
 *		no return value.
 */
void releaseTimer(Timer *timer);

/* 
 * Get the total timing count, that is just the past timing interrupt count since the 
 * system is started.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		the total timing count.
 */
u64 getTime();
