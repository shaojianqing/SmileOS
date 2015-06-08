typedef struct Timer
{	
	u64 timeout;

	u8 status;

	u8 data;

	QueueBuffer *queue;
} Timer;

typedef struct TimerManager
{
	u64 time;

	u64 latest;

	u32 using;

	Timer *timerArray[MAX_TIMER_NUM];

	Timer timerList[MAX_TIMER_NUM];
} TimerManager;

TimerManager timeManager;

void intHandler20()
{
	outByte(PIC0_OCW2, 0x60);
	timeManager.time++;

	if (timeManager.latest<timeManager.time) {
		timeManager.latest=0xffffffff;
		int i=0;
		if (timeManager.using>0) {
			if ((*(timeManager.timerArray[0])).timeout<timeManager.time) {
				putQueueBuffer((*(timeManager.timerArray[0])).queue, (*(timeManager.timerArray[0])).data);			
			}
			timeManager.using--;
			for (i=0;i<timeManager.using;++i) {
				timeManager.timerArray[i] = timeManager.timerArray[i+1];
			}
			if (timeManager.using>0) {
				timeManager.latest = (*(timeManager.timerArray[0])).timeout;	
			}
			timeManager.timerArray[timeManager.using] = null;
			(*(timeManager.timerArray[timeManager.using])).status = STATUS_TIMER_UNUSE;
		}		
	}
}

void initTimerManagement()
{
	timeManager.time=0;
	timeManager.using=0;
	timeManager.latest=0xffffffff;
	int i=0;
	for (i=0;i<MAX_TIMER_NUM;++i) {
		Timer timer = timeManager.timerList[i];
		timer.status = STATUS_TIMER_UNUSE;
	}
}

Timer* requestTimer(u64 timeout, QueueBuffer *queue)
{
	clearInterrupt();
	int i=0, j=0;
	if (timeManager.using<MAX_TIMER_NUM) {
		Timer *timer = null;
		for (i=0;i<MAX_TIMER_NUM;++i) {
			if (timeManager.timerList[i].status == STATUS_TIMER_UNUSE) {
				timeManager.timerList[i].status = STATUS_TIMER_USING;
				timeManager.timerList[i].timeout = timeout;
				timeManager.timerList[i].queue = queue;			
				if (timeManager.latest>timeout) {
					timeManager.latest=timeout;
				}
				timer = &timeManager.timerList[i];
				break;		
			}
		}
		if (timer != null) {
			if (timeManager.using==0) {
				timeManager.timerArray[0] = timer;
			} else {
				if ((*timer).timeout>=(*(timeManager.timerArray[timeManager.using-1])).timeout) {
					timeManager.timerArray[timeManager.using] = timer;
				} else {
					for (i=0;i<timeManager.using;++i) {
						if ((*timer).timeout<(*(timeManager.timerArray[i])).timeout) {
							for (j=i;j<timeManager.using+1;++j) {
								timeManager.timerArray[j+1] = timeManager.timerArray[j];								
							}
							timeManager.timerArray[i] = timer;
							break;
						}
					}
				}			
			}
			timeManager.latest = (*(timeManager.timerArray[0])).timeout;
			timeManager.using++;
			setupInterrupt();
			return timer;
		}
	}
	setupInterrupt();
	return null;
}

void releaseTimer(Timer *timer)
{
	if (timer!=null) {
		(*timer).status = STATUS_TIMER_UNUSE;
	}
}

u64 getTime()
{
	return timeManager.time;
}
