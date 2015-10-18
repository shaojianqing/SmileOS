#include "type/type.h"
#include "const/const.h"
#include "algorithm/algorithm.h"
#include "macro/macro.h"
#include "inOutput/inOutput.h"
#include "memory/memory.h"
#include "gui/color.h"
#include "gui/video.h"
#include "gui/sheet.h"
#include "gui/image.h"
#include "gui/corner.h"
#include "gui/window.h"
#include "gui/charset.h"
#include "gui/desktop.h"
#include "gui/graphics.h"
#include "system/descriptor.h"
#include "execute/execute.h"
#include "process/process.h"
#include "system/globalData.h"
#include "system/interrupt.h"
#include "include/timing.h"
#include "include/mouse.h"
#include "include/harddisk.h"
#include "include/keyboard.h"
#include "include/peripheral.h"
#include "interface/interface.h"

int mx=500, my=380;

MouseData mouseData;

KeyData keyData;

Sheet *testSheet;

Process *kernelProcess;

Process *commandProcess;

Process *sysInfoProcess;

Process *dataGraphProcess;

Process *calculatorProcess;

Process *mathematicsProcess;

extern Sheet *mouse;

extern Sheet *background;

extern Sheet *infoBarSheet;

extern Sheet *startBarSheet;

int testCallGate(int color)
{
	u8 *buffer = (u8*)0xe0000000;
	int i=0;
	for (i=0;i<1024*100*3;i+=3) {
		*(buffer+i) = (color & 0xFF);
		*(buffer+i+1) = (color>>8 & 0xFF);	
		*(buffer+i+2) = (color>>16 & 0xFF);	
	}
	return color+8;
}

void initSystem(void)
{
    mouseData.phase = 0;
 	
	initVideoModeInfo();
	initInterfaceTable();
	initInterruptHandler();
	initQueueBufferData();
	initTimerManagement();
	initPeripheralStatus();

	initKeyTableSetting();

    initMemoryManagement();
    initSheetManagement();
	initProcessManagement();
	prepareKernelProcess();
	initDesktopInfoSheet();

	testSheet = prepareSheet();
	prepareTestSheet(testSheet);
	loadWindowSheet(testSheet);

    while(TRUE) {
        clearInterrupt();
		if (queueBufferStatus(&systemBuffer) == 0) {
			setupInterrupt();		
		} else {
			u32 data = getQueueBuffer(&systemBuffer);
			if (data<1024) {
				setupInterrupt();
			} else if (data>=1024 && data<2048) {
				Sheet *commandWindow = (*commandProcess).mainWindow;
				processKeyData(&keyData, data, commandWindow);			
			} else if (data>=2048) {
				processMouseData(&mouseData, data, mouse, &mx, &my);
			}
		}
    }	
}

