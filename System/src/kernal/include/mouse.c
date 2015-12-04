#include "../const/const.h"
#include "../type/type.h"
#include "../algorithm/algorithm.h"
#include "../gui/sheet.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "mouse.h"

extern int currentDesktopIndex;

extern QueueBuffer systemBuffer;

extern Sheet *testSheet;

extern Sheet *background;

extern Sheet *startBarSheet;

extern Process *mathematicsProcess;

extern Process *calculatorProcess;

int count =91;

void intHandler2c()
{
	u32 data;
	outByte(PIC1_OCW2, 0x64);
	outByte(PIC0_OCW2, 0x62);
	data = inByte(PORT_KEYDATA) + 2048;
	putQueueBuffer(&systemBuffer, data);
	switchKernelProcess();
}

void drawMouseMap(char *buffer)
{
    int mouseMap[MOUSE_HEIGHT][MOUSE_WIDTH] = {'@','~','~','~','~','~','~','~','~','~','~','~',
                                               '@','@','~','~','~','~','~','~','~','~','~','~',
                                               '@','#','@','~','~','~','~','~','~','~','~','~',
                                               '@','#','#','@','~','~','~','~','~','~','~','~',
                                               '@','#','#','#','@','~','~','~','~','~','~','~',
                                               '@','#','#','#','#','@','~','~','~','~','~','~',
                                               '@','#','#','#','#','#','@','~','~','~','~','~',
                                               '@','#','#','#','#','#','#','@','~','~','~','~',
                                               '@','#','#','#','#','#','#','#','@','~','~','~',
                                               '@','#','#','#','#','#','#','#','#','@','~','~',
                                               '@','#','#','#','#','#','#','#','#','#','@','~',
                                               '@','#','#','#','#','#','#','@','@','@','@','@',
                                               '@','#','#','#','@','#','#','@','~','~','~','~',
                                               '@','#','#','@','@','#','#','@','~','~','~','~',
                                               '@','#','@','~','~','@','#','#','@','~','~','~',
                                               '@','@','~','~','~','@','#','#','@','~','~','~',
                                               '@','~','~','~','~','~','@','#','#','@','~','~',
                                               '~','~','~','~','~','~','@','#','#','@','~','~',
                                               '~','~','~','~','~','~','~','@','#','#','@','~',
                                               '~','~','~','~','~','~','~','@','#','#','@','~',
                                               '~','~','~','~','~','~','~','~','@','@','~','~'
                                              };

    int i=0, j=0;
    for (i=0; i<22; ++i) {
        for (j=0; j<MOUSE_WIDTH; ++j) {
            if (mouseMap[i][j] == '@') {
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY) = 20;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 1) = 20;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 2) = 20;
            } else if (mouseMap[i][j] == '#') {
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY) = 255;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 1) = 255;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 2) = 255;
            } else {
				*(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY) = 0;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 1) = 0;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 2) = 0;		
			}
        }
    }
}

Sheet *prepareMouseSheet(Sheet* sheet)
{
    if (sheet != 0) {
        (*sheet).buffer = (char *)alloc(MOUSE_WIDTH*MOUSE_HEIGHT*SCREEN_DENSITY);
        (*sheet).x = 500;
        (*sheet).y = 380;
        (*sheet).width = MOUSE_WIDTH;
        (*sheet).height = MOUSE_HEIGHT;
        drawMouseMap((*sheet).buffer);
    }
}

void processMouseData(MouseData *mouseData, u32 data, Sheet *mouse, int *mx, int *my)
{
    setupInterrupt();
	u8 sign = data-2048;
    setupInterrupt();
    if ((*mouseData).phase == 0) {
        if (sign == 0xfa) {
            (*mouseData).phase = 1;
        }
    } else if ((*mouseData).phase == 1) {
        if ((sign & 0xc8) == 0x08) {
            (*mouseData).buf[0] = sign;
            (*mouseData).phase = 2;
        }
    } else if ((*mouseData).phase == 2) {
        (*mouseData).buf[1] = sign;
        (*mouseData).phase = 3;
    } else if ((*mouseData).phase == 3) {
        (*mouseData).buf[2] = sign;
        (*mouseData).phase = 1;
        (*mouseData).btn = (*mouseData).buf[0] & 0x07;
        (*mouseData).x = (*mouseData).buf[1];
        (*mouseData).y = (*mouseData).buf[2];

        if (((*mouseData).buf[0] & 0x10) != 0) {
            (*mouseData).x |= 0xffffff00;
        }

        if (((*mouseData).buf[0] & 0x20) != 0) {
            (*mouseData).y |= 0xffffff00;
        }

        (*mouseData).y = 0 - (*mouseData).y;

        *mx += (*mouseData).x;
        *my += (*mouseData).y;

        if (*mx>SCREEN_WIDTH) {
            *mx=SCREEN_WIDTH;
        }
        if (*mx<0) {
            *mx=0;
        }

        if (*my>SCREEN_HEIGHT) {
            *my=SCREEN_HEIGHT;
        }
        if (*my<0) {
            *my=0;
        }
        slideSheet(mouse, (*mx), (*my));

		if ((*mouseData).btn==MOUSE_DOWN_EVENT) {	
			Sheet *sheet = getCurrentSheet((*mx), (*my));
			if (isSheetTop(sheet)==TRUE) {
				processSheetMouseDownEvent(sheet, (*mx), (*my));		
			} else {
				setSheetTop(sheet);
			}
		}
    }
}
