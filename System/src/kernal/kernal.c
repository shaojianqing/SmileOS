#include "const/const.h"
#include "structure/structure.h"
#include "structure/algorithm.c"
#include "macro/macro.h"
#include "inOutput/inOutput.h"
#include "harddisk/hd.c"
#include "memory/memory.c"
#include "sheet/sheet.c"
#include "timing/timing.c"
#include "include/mouse.c"
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

    mx = 500;
    my = 360;
    while(TRUE)
    {
        clearInterrupt();
		if (queueBufferStatus(&keyBuffer) + queueBufferStatus(&mouseBuffer) == 0) {
			setupInterrupt();
		} else {
			if (queueBufferStatus(&keyBuffer) != 0) {
				processKeyData(&keyData, window);
			} else if (queueBufferStatus(&mouseBuffer) != 0) {
				processMouseData(&mouseData, mouse, &mx, &my);
			}
		}
    }
}

