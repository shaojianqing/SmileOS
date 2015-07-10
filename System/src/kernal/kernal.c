#include "const/const.h"
#include "structure/structure.h"
#include "structure/algorithm.c"
#include "macro/macro.h"
#include "inOutput/inOutput.h"
#include "memory/memory.c"
#include "process/process.h"
#include "gui/sheet.h"
#include "gui/image.h"
#include "graphics/graphics.c"
#include "charset/charset.c"
#include "include/globalData.c"
#include "include/timing.c"
#include "include/mouse.c"
#include "include/harddisk.c"
#include "include/keyboard.c"
#include "include/descriptor.c"
#include "include/interrupt.c"
#include "include/peripheral.c"
#include "window/window.c"
#include "desktop/desktop.c"
#include "background/background.c"

int mx, my;

MouseData mouseData;

KeyData keyData;

Sheet *window;

Sheet *mouse;

Process *userProcess;

Sheet *getWindow()
{
	return window;
}

void processA()
{
	Sheet *window = getWindow();
	
	int count = 0;

	Color mainColor;
    mainColor.red = 240;
    mainColor.green = 100;
    mainColor.blue = 100;

	Color color;
    color.red = 240;
    color.green = 240;
    color.blue = 240;	

	while(TRUE) {
		count++;
		drawRect((*window).buffer, window, 60, 70, 120, 100, color);
		printInteger(window, count, 100, 80, mainColor);

		refreshSheetMap((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, 0);
    	refreshSheetSub((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, (*window).z, (*window).z);		
	}
}

void initSystem(void)
{
    mouseData.phase = 0;

	initInterruptHandler();	
	initQueueBufferData();
	initTimerManagement();
	initPeripheralStatus();

	initKeyTableSetting();

    initMemoryManagement();
    initSheetManagement();
	initProcessManagement();

    Sheet *background = prepareSheet();
    prepareBackgroundSheet(background);
    loadSheet(background, 0);

    window = prepareSheet();
    prepareWindowSheet(window);
    loadSheet(window, 1);

    mouse = prepareSheet();
    prepareMouseSheet(mouse);
    loadSheet(mouse, 2);

	Timer* time1 = requestTimer(0500, 1, &systemBuffer);
	Timer* time2 = requestTimer(1000, 2, &systemBuffer);
	Timer* time3 = requestTimer(1500, 3, &systemBuffer);
	Timer* time4 = requestTimer(2000, 4, &systemBuffer);
	Timer* time5 = requestTimer(2500, 5, &systemBuffer);
	
    mx = 640;
    my = 512;

	userProcess = requestProcess();

	(*userProcess).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
	(*userProcess).tss.eip = (int) &processA;
	(*userProcess).tss.es = 2 * 8;
	(*userProcess).tss.cs = 1 * 8;
	(*userProcess).tss.ss = 2 * 8;
	(*userProcess).tss.ds = 2 * 8;
	(*userProcess).tss.fs = 2 * 8;
	(*userProcess).tss.gs = 2 * 8;
	startRunProcess(userProcess);

    while(TRUE) {
        clearInterrupt();
		if (queueBufferStatus(&systemBuffer) == 0) {
			setupInterrupt();
		} else {
			u32 data = getQueueBuffer(&systemBuffer);
			if (data<1024) {
				if (data == 1) {
					showInfo(window, 40, 100, 11);	
				} else if (data == 2) {
					showInfo(window, 40, 140, 22);			
				} else if (data == 3) {
					showInfo(window, 40, 180, 33);								
				} else if (data == 4) {
					showInfo(window, 40, 220, 44);			
				} else if (data == 5) {
					showInfo(window, 40, 260, 55);	
				}
				setupInterrupt();
			} else if (data>=1024 && data<2048) {
				processKeyData(&keyData, data, window);			
			} else if (data>=2048) {
				processMouseData(&mouseData, data, mouse, &mx, &my);
				if ((mouseData.btn & 0x01) != 0) {
					slideSheet(window, mx, my);				
				}
			}
		}
    }	
}

