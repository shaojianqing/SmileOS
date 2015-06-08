#include "const/const.h"
#include "structure/structure.h"
#include "structure/algorithm.c"
#include "macro/macro.h"
#include "inOutput/inOutput.h"
#include "memory/memory.c"
#include "sheet/sheet.c"
#include "include/timing.c"
#include "include/mouse.c"
#include "include/harddisk.c"
#include "include/keyboard.c"
#include "include/descriptor.c"
#include "include/interrupt.c"
#include "include/peripheral.c"
#include "charset/charset.c"
#include "gui/image.c"
#include "graphics/graphics.c"
#include "window/window.c"
#include "desktop/desktop.c"
#include "background/background.c"

u8 timeQueueBuffer1[8], timeQueueBuffer2[8], timeQueueBuffer3[8], timeQueueBuffer4[8];

QueueBuffer timeQueue1, timeQueue2, timeQueue3, timeQueue4;

int mx, my;

MouseData mouseData;

KeyData keyData;

Sheet *window;

Sheet *mouse;

void initSystem(void)
{	
    mouseData.phase = 0;

	initInterruptHandler();	
	initQueueBufferData();
	initTimerManagement();
	initPeripheralStatus();

    initMemoryManagement();
    initSheetManagement();

    Sheet *background = prepareSheet();
    prepareBackgroundSheet(background);
    loadSheet(background, 0);

    window = prepareSheet();
    prepareWindowSheet(window);
    loadSheet(window, 1);

    mouse = prepareSheet();
    prepareMouseSheet(mouse);
    loadSheet(mouse, 2);

	initQueueBuffer(&timeQueue1, 8, timeQueueBuffer1);
	initQueueBuffer(&timeQueue2, 8, timeQueueBuffer2);
	initQueueBuffer(&timeQueue3, 8, timeQueueBuffer3);
	initQueueBuffer(&timeQueue4, 8, timeQueueBuffer4);

	Timer* time1 = requestTimer(1000, &timeQueue1);
	Timer* time2 = requestTimer(1500, &timeQueue2);
	Timer* time3 = requestTimer(5000, &timeQueue3);
	Timer* time4 = requestTimer(8000, &timeQueue4);
	

    mx = 640;
    my = 512;

	//showBufferInfo(window, (u8 *)0xe0000000);

    while(TRUE) {
        clearInterrupt();
		if (queueBufferStatus(&keyBuffer) + queueBufferStatus(&mouseBuffer) + queueBufferStatus(&timeQueue1) +
			queueBufferStatus(&timeQueue2) + queueBufferStatus(&timeQueue3) + queueBufferStatus(&timeQueue4) == 0) {
			setupInterrupt();
		} else {
			if (queueBufferStatus(&keyBuffer) != 0) {
				processKeyData(&keyData, window);
			}
			if (queueBufferStatus(&mouseBuffer) != 0) {
				processMouseData(&mouseData, mouse, &mx, &my);
			}
			if (queueBufferStatus(&timeQueue1) != 0) {
				u8 data = getQueueBuffer(&timeQueue1);
				showInfo(window, 100, 100, 66);
				setupInterrupt();
			}
			if (queueBufferStatus(&timeQueue2) != 0) {
				u8 data = getQueueBuffer(&timeQueue2);
				showInfo(window, 100, 160, 77);
				setupInterrupt();
			}
			if (queueBufferStatus(&timeQueue3) != 0) {
				u8 data = getQueueBuffer(&timeQueue3);
				showInfo(window, 100, 220, 88);
				setupInterrupt();
			}
			if (queueBufferStatus(&timeQueue4) != 0) {
				u8 data = getQueueBuffer(&timeQueue4);
				showInfo(window, 100, 280, 99);
				setupInterrupt();
			}
		}
    }
}

