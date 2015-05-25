
typedef struct TimerManager
{
	u64 time;
} TimerManager;

TimerManager timeManager;

void intHandler20()
{
	outByte(PIC0_OCW2, 0x60);
	timeManager.time++;
}

void initTimerManagement()
{
	timeManager.time=0;
}

u64 getTime()
{
	return timeManager.time;
}
