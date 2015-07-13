#include "../const/const.h"
#include "../type/type.h"
#include "../algorithm/algorithm.h"
#include "timing.h"

TimerManager timeManager;

void intHandler20()
{
	outByte(PIC0_OCW2, 0x60);
	timeManager.time++;

	if (timeManager.latest<timeManager.time) {
		timeManager.latest=0xffffffff;
		Timer *timer = timeManager.currentTimer;
		if (timer != null && (*timer).timeout<timeManager.time) {
			putQueueBuffer((*(timer)).queue, (*(timer)).data);
			(*timer).status = STATUS_TIMER_UNUSE;
			if ((*timer).next != null) {
				timer = (*timer).next;
				timeManager.currentTimer = timer;
				timeManager.latest = (*timer).timeout;
			} else {
				timeManager.currentTimer = null;
			}				
		}		
	}
	startSwitchProcess();
}

void initTimerManagement()
{
	timeManager.time=0;
	timeManager.latest=0xffffffff;
	timeManager.currentTimer = null;
	int i=0;
	for (i=0;i<MAX_TIMER_NUM;++i) {
		Timer timer = timeManager.timerList[i];
		timer.status = STATUS_TIMER_UNUSE;
	}
}

Timer* requestTimer(u64 timeout, u8 data, QueueBuffer *queue)
{
	clearInterrupt();
	int i=0, j=0;
	Timer *timer = null;
	for (i=0;i<MAX_TIMER_NUM;++i) {
		if (timeManager.timerList[i].status == STATUS_TIMER_UNUSE) {
			timeManager.timerList[i].status = STATUS_TIMER_USING;
			timeManager.timerList[i].timeout = timeout;
			timeManager.timerList[i].queue = queue;
			timeManager.timerList[i].next = null;
			timeManager.timerList[i].data = data;	
			if (timeManager.latest>timeout) {
				timeManager.latest=timeout;
			}
			timer = &timeManager.timerList[i];
			break;		
		}
	}
	if (timer != null) {
		if (timeManager.currentTimer==null) {
			timeManager.currentTimer = timer;
		} else {
			Timer *prevTimer = timeManager.currentTimer, *nextTimer = null;				
			if ((*prevTimer).timeout>(*timer).timeout) {
				(*timer).next = prevTimer;
				timeManager.currentTimer = timer;
			} else {
				while(TRUE) {
					nextTimer = (*prevTimer).next;
					if (nextTimer != null) {	
						if ((*nextTimer).timeout>(*timer).timeout) {
							(*prevTimer).next = timer;
							(*timer).next = nextTimer;	
							break;				
						} else {
							prevTimer = nextTimer;				
						}
					} else {
						(*prevTimer).next = timer;
						break;							
					}
				}
			}
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
