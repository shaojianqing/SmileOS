#include "structure/structure.h"
#include "macro/macro.h"
#include "io/io.h"
#include "harddisk/hd.c"
#include "memory/memory.c"
#include "const/const.h"
#include "timing/timing.c"
#include "include/descriptor.c"
#include "include/interrupt.c"
#include "sheet/sheet.c"
#include "charset/charset.c"
#include "keyboard/keyboard.c"
#include "gui/image.c"
#include "graphics/graphics.c"
#include "mouse/mouse.c"
#include "window/window.c"
#include "desktop/desktop.c"
#include "background/background.c"

int mx, my;

MouseData mouseData;

void initSystem(void)
{

    mouseData.phase = 0;

    unsigned int count = 0;

	initInterruptHandler();
    initMemoryManagement();
    initSheetManagement();

    Sheet *background = prepareSheet();
    prepareBackgroundSheet(background);
    loadSheet(background, 0);

    /*Sheet *infoBar = prepareSheet();
    prepareInfoBarSheet(infoBar);
    loadSheet(infoBar, 1);*/

    /*Sheet *startBar = prepareSheet();
    prepareStartBarSheet(startBar);
    loadSheet(startBar, 1);*/

    Sheet *window = prepareSheet();
    prepareWindowSheet(window);
    loadSheet(window, 1);

    Sheet *mouse = prepareSheet();
    prepareMouseSheet(mouse);
    loadSheet(mouse, 2);

    //unsigned int size2 = memorySize();
    //printInteger(size2, 300, 420, blockColor);

    //printChar('M', 100, 100, blockColor);

    //drawRect(50, 50, 200, 200, blockColor);

    /*Color startColor;
    startColor.red = 240;
    startColor.green = 240;
    startColor.blue = 240;

    Color endColor;
    endColor.red = 160;
    endColor.green = 160;
    endColor.blue = 160;

    Corner corner;
    corner.leftTop = 2;
    corner.rightTop = 10;
    corner.leftBtm = 10;
    corner.rightBtm = 10;

    drawGradualVerticalCornerRect(100, 300, 400, 400, startColor, endColor, corner);*/

    /*Color circleColor;
    circleColor.red = 255;
    circleColor.green = 40;
    circleColor.blue = 100;
    drawCircle(800, 200, 100, circleColor);

    printChar('%', 200, 100, blockColor);*/

    mx = 500;
    my = 360;
    
    initMouseBuffer();
	u8 *a = (u8 *)0x30401;
	showInfo(window, (int)intHandler20);

    for (;;)
    {

        
        //MouseBuffer *mouseBuffer = (MouseBuffer *)0x21000;
        //clearInterrupt();






        //processKeyData(window);
        processMouseData(&mouseData, mouse, &mx, &my);


    }
}

