#include "type/type.h"
#include "const/const.h"
#include "algorithm/algorithm.h"
#include "macro/macro.h"
#include "inOutput/inOutput.h"
#include "memory/memory.h"
#include "process/process.h"
#include "gui/color.h"
#include "gui/video.h"
#include "gui/sheet.h"
#include "gui/back.h"
#include "gui/image.h"
#include "gui/corner.h"
#include "gui/window.h"
#include "gui/charset.h"
#include "gui/desktop.h"
#include "gui/graphics.h"
#include "system/globalData.h"
#include "system/interrupt.h"
#include "system/descriptor.h"
#include "include/timing.h"
#include "include/mouse.h"
#include "include/harddisk.h"
#include "include/keyboard.h"
#include "include/peripheral.h"

int mx, my;

MouseData mouseData;

KeyData keyData;

Sheet *windowOne;

Sheet *windowTwo;

Sheet *windowThree;

Sheet *windowFour;

Sheet *mouse;

Process *kernelProcess;

Process *userProcessOne;

Process *userProcessTwo;

Process *userProcessThree;

Process *userProcessFour;

Sheet *getWindowOne()
{
	return windowOne;
}

Sheet *getWindowTwo()
{
	return windowTwo;
}

Sheet *getWindowThree()
{
	return windowThree;
}

Sheet *getWindowFour()
{
	return windowFour;
}

void processA()
{
	Sheet *window = getWindowOne();
	
	int count = 0;

	Color mainColor;
    mainColor.red = 160;
    mainColor.green = 160;
    mainColor.blue = 20;

	Color color;
    color.red = 220;
    color.green = 220;
    color.blue = 220;	

	while(TRUE) {
		count++;
		drawRect((*window).buffer, window, 20, 70, 120, 100, color);
		printInteger(window, count, 100, 80, mainColor);

		refreshSheetMap((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, 0);
    	refreshSheetSub((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, (*window).z, (*window).z);	

		if (count==200) {
			startSleepProcess(userProcessOne);		
		}
	}
}

void processB()
{
	Sheet *window = getWindowTwo();
	
	int count = 0;

	Color mainColor;
    mainColor.red = 240;
    mainColor.green = 20;
    mainColor.blue = 240;

	Color color;
    color.red = 220;
    color.green = 220;
    color.blue = 220;	

	while(TRUE) {
		count++;
		drawRect((*window).buffer, window, 20, 70, 120, 100, color);
		printInteger(window, count, 100, 80, mainColor);

		refreshSheetMap((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, 0);
    	refreshSheetSub((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, (*window).z, (*window).z);	

		if (count==300) {
			startSleepProcess(userProcessTwo);		
		}
	}
}

void processC()
{
	Sheet *window = getWindowThree();
	
	int count = 0;

	Color mainColor;
    mainColor.red = 20;
    mainColor.green = 180;
    mainColor.blue = 180;

	Color color;
    color.red = 220;
    color.green = 220;
    color.blue = 220;	

	while(TRUE) {
		count++;
		drawRect((*window).buffer, window, 20, 70, 120, 100, color);
		printInteger(window, count, 100, 80, mainColor);

		refreshSheetMap((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, 0);
    	refreshSheetSub((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, (*window).z, (*window).z);	

		if (count==2000) {
			startSleepProcess(userProcessThree);		
		}
	}
}

void processD()
{
	Sheet *window = getWindowFour();
	
	int count = 0;

	Color mainColor;
    mainColor.red = 120;
    mainColor.green = 60;
    mainColor.blue = 240;

	Color color;
    color.red = 220;
    color.green = 220;
    color.blue = 220;	

	while(TRUE) {
		count++;
		drawRect((*window).buffer, window, 20, 70, 120, 100, color);
		printInteger(window, count, 100, 80, mainColor);

		refreshSheetMap((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, 0);
    	refreshSheetSub((*window).x, (*window).y, (*window).x+(*window).width, (*window).y+(*window).height, (*window).z, (*window).z);	

		if (count==2000) {
			startSleepProcess(userProcessFour);		
		}
	}
}

void initSystem(void)
{
    mouseData.phase = 0;
 	
	initVideoModeInfo();
	initInterruptHandler();	
	initQueueBufferData();
	initTimerManagement();
	initPeripheralStatus();

	initKeyTableSetting();

    initMemoryManagement();
    initSheetManagement();
	initProcessManagement();
	prepareKernelProcess();

    Sheet *background = prepareSheet();
    prepareBackgroundSheet(background);
    loadSheet(background, 0);

    windowOne = prepareSheet();
    prepareWindowSheetOne(windowOne);
    loadSheet(windowOne, 1);

	windowTwo = prepareSheet();
    prepareWindowSheetTwo(windowTwo);
    loadSheet(windowTwo, 2);

	windowThree = prepareSheet();
    prepareWindowSheetThree(windowThree);
    loadSheet(windowThree, 3);

	windowFour = prepareSheet();
    prepareWindowSheetFour(windowFour);
    loadSheet(windowFour, 4);

    mouse = prepareSheet();
    prepareMouseSheet(mouse);
    loadSheet(mouse, 5);
	
    mx = 500;
    my = 380;

	userProcessOne = requestProcess();

	(*userProcessOne).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
	(*userProcessOne).tss.eip = (int) &processA;
	(*userProcessOne).tss.es = 2 * 8;
	(*userProcessOne).tss.cs = 1 * 8;
	(*userProcessOne).tss.ss = 2 * 8;
	(*userProcessOne).tss.ds = 2 * 8;
	(*userProcessOne).tss.fs = 2 * 8;
	(*userProcessOne).tss.gs = 2 * 8;
	startRunProcess(userProcessOne, 1, 1);

	userProcessTwo = requestProcess();

	(*userProcessTwo).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
	(*userProcessTwo).tss.eip = (int) &processB;
	(*userProcessTwo).tss.es = 2 * 8;
	(*userProcessTwo).tss.cs = 1 * 8;
	(*userProcessTwo).tss.ss = 2 * 8;
	(*userProcessTwo).tss.ds = 2 * 8;
	(*userProcessTwo).tss.fs = 2 * 8;
	(*userProcessTwo).tss.gs = 2 * 8;
	startRunProcess(userProcessTwo, 1, 1);

	userProcessThree = requestProcess();

	(*userProcessThree).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
	(*userProcessThree).tss.eip = (int) &processC;
	(*userProcessThree).tss.es = 2 * 8;
	(*userProcessThree).tss.cs = 1 * 8;
	(*userProcessThree).tss.ss = 2 * 8;
	(*userProcessThree).tss.ds = 2 * 8;
	(*userProcessThree).tss.fs = 2 * 8;
	(*userProcessThree).tss.gs = 2 * 8;
	startRunProcess(userProcessThree, 2, 1);

	userProcessFour = requestProcess();

	(*userProcessFour).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
	(*userProcessFour).tss.eip = (int) &processD;
	(*userProcessFour).tss.es = 2 * 8;
	(*userProcessFour).tss.cs = 1 * 8;
	(*userProcessFour).tss.ss = 2 * 8;
	(*userProcessFour).tss.ds = 2 * 8;
	(*userProcessFour).tss.fs = 2 * 8;
	(*userProcessFour).tss.gs = 2 * 8;
	startRunProcess(userProcessFour, 2, 1);


    while(TRUE) {
        clearInterrupt();
		if (queueBufferStatus(&systemBuffer) == 0) {
			startSleepProcess(kernelProcess);
			setupInterrupt();
		} else {
			u32 data = getQueueBuffer(&systemBuffer);
			if (data<1024) {
				setupInterrupt();
			} else if (data>=1024 && data<2048) {
				processKeyData(&keyData, data, windowOne);			
			} else if (data>=2048) {
				processMouseData(&mouseData, data, mouse, &mx, &my);
			}
		}
    }	
}

