#include "../const/const.h"
#include "../type/type.h"
#include "../memory/memory.h"
#include "view/view.h"
#include "sheet.h"
#include "color.h"
#include "corner.h"
#include "graphics.h"
#include "test.h"

extern Sheet *testSheet;

Sheet* prepareTestSheet(Sheet *sheet)
{
    if (sheet!=null) {
        (*sheet).x = 112;
        (*sheet).y = 40;
        (*sheet).width = 800;
        (*sheet).height = 600;
		(*sheet).buffer = (char *)allocPage(800*600*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 800, 600);

        Color startColor;
        startColor.red = 250;
        startColor.green = 250;
        startColor.blue = 250;

        Color endColor;
        endColor.red = 220;
        endColor.green = 220;
        endColor.blue = 220;

        Corner corner;
        corner.leftTop=2;
        corner.rightTop=2;
        corner.leftBtm=0;
        corner.rightBtm=0;

        Color mainBgColor;
        mainBgColor.red = 120;
        mainBgColor.green = 120;
        mainBgColor.blue = 120;

        Color mainColor;
        mainColor.red = 20;
        mainColor.green = 40;
        mainColor.blue = 60;

		Color txtBorderColor;
        txtBorderColor.red = 160;
        txtBorderColor.green = 160;
        txtBorderColor.blue = 160;

		drawCornerRect(mainView, 0, 0, (*mainView).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 20, startColor, endColor, corner, DIRECTION_UP);
        drawRect(mainView, 0, 21, (*mainView).width, 579, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 577, mainColor);

		loadContentView(sheet, mainView);

        return sheet;
    }
}

void showLetter(int x, int y) 
{
	Color mainColor;
    mainColor.red = 255;
    mainColor.green = 255;
    mainColor.blue = 255;

	Color shadowColor;
    shadowColor.red = 80;
    shadowColor.green = 160;
    shadowColor.blue = 240;

	View *mainView = (*testSheet).contentView;
	printString(mainView, "AAAabcdefghijklmnopqrstuvwxyzBBB", 32, x, y, mainColor, shadowColor);
	(*mainView).refreshRectView(mainView);
}

void showIntegerValue(int value, int x, int y)
{
	Color mainColor;
    mainColor.red = 20;
    mainColor.green = 40;
    mainColor.blue = 60;

    Color fontColor;
    fontColor.red = 250;
    fontColor.green = 88;
    fontColor.blue = 22;

	Color shadowColor;
    shadowColor.red = 250;
    shadowColor.green = 88;
    shadowColor.blue = 22;

	View *mainView = (*testSheet).contentView;

    drawRect(mainView, x-80, y, 200, 20, mainColor);
    printHexInteger(mainView, value, x, y, fontColor, shadowColor);
	(*mainView).refreshRectView(mainView);
}

void showBufferData(char *buffer)
{
	Color mainColor;
    mainColor.red = 240;
    mainColor.green = 200;
    mainColor.blue = 66;

	Color shadowColor;
    shadowColor.red = 240;
    shadowColor.green = 200;
    shadowColor.blue = 66;	
		
	int totalSize = 256, rowNum = 16, columnNum = 16;
	View *mainView = (*testSheet).contentView;

	int x=0,y=0;
	for (y=0;y<columnNum;++y) {
		for (x=0;x<rowNum;++x) {
			char data= *(buffer+y*16+x);
			printHexByte(mainView, data, x*28+340, y*28+44, mainColor, shadowColor);
		}	
	}

	(*mainView).refreshRectView(mainView);
}

void printMemoryTable(View *view)
{
	if (view!=null) {

		Color topColor;
        topColor.red = 240;
        topColor.green = 240;
        topColor.blue = 80;

		Color shadowColor;
        shadowColor.red = 240;
        shadowColor.green = 240;
        shadowColor.blue = 80;

		Color titleColor;
        titleColor.red = 240;
        titleColor.green = 60;
        titleColor.blue = 240;

		Color addrColor;
        addrColor.red = 240;
        addrColor.green = 200;
        addrColor.blue = 240;

		Color pointColor;
        pointColor.red = 20;
        pointColor.green = 250;
        pointColor.blue = 240;

		Color sizeColor;
        sizeColor.red = 240;
        sizeColor.green = 200;
        sizeColor.blue = 40;

		Color bgColor;
    	bgColor.red = 240;
    	bgColor.green = 240;
    	bgColor.blue = 240;

		Color mainColor;
        mainColor.red = 20;
        mainColor.green = 40;
        mainColor.blue = 60;

		printString(view, "Memory Allocation Table", 23, 450, 44, topColor, shadowColor);

		drawRect(view, 349, 69, 402, 502, bgColor);
		drawRect(view, 350, 70, 400, 500, mainColor);

		drawLine(view, 350, 94, 750, 95, bgColor, LINE_THIN);
		drawLine(view, 420, 69, 420, 570, bgColor, LINE_THIN);
		drawLine(view, 495, 69, 495, 570, bgColor, LINE_THIN);
		drawLine(view, 570, 69, 570, 570, bgColor, LINE_THIN);
		drawLine(view, 650, 69, 650, 570, bgColor, LINE_THIN);
		drawLine(view, 710, 69, 710, 570, bgColor, LINE_THIN);
		
		printString(view, "Addr", 4, 360, 74, titleColor, shadowColor);		
		printString(view, "Point", 5, 430, 74, titleColor, shadowColor);
		printString(view, "Prev", 4, 505, 74, titleColor, shadowColor);
		printString(view, "Next", 4, 580, 74, titleColor, shadowColor);
		printString(view, "Size", 4, 660, 74, titleColor, shadowColor);
		printString(view, "ST", 2, 720, 74, titleColor, shadowColor);

		MemoryManager *memoryManager = (MemoryManager *)MEM_MANAGE_BASE;
		MemoryInfo *currentMemoryInfo = (*memoryManager).firstMemoryInfo;

		Color statusColor;

		int i=1;
		while (currentMemoryInfo!=null) {
			if ((*currentMemoryInfo).status==STATUS_UNALLOC) {
        		statusColor.red = 40;
        		statusColor.green = 240;
        		statusColor.blue = 40;
			} else if ((*currentMemoryInfo).status==STATUS_ALLOCED) {
				statusColor.red = 240;
        		statusColor.green = 40;
        		statusColor.blue = 40;
			}

			printHexInteger(view, (*currentMemoryInfo).addr, 400, 100+(i-1)*30, addrColor, shadowColor);
			printHexInteger(view, currentMemoryInfo, 475, 100+(i-1)*30, pointColor, shadowColor);
			printHexInteger(view, (*currentMemoryInfo).prev, 550, 100+(i-1)*30, pointColor, shadowColor);
			printHexInteger(view, (*currentMemoryInfo).next, 625, 100+(i-1)*30, pointColor, shadowColor);
			printHexInteger(view, (*currentMemoryInfo).size, 700, 100+(i-1)*30, sizeColor, shadowColor);
			printHexByte(view, (*currentMemoryInfo).status, 730, 100+(i-1)*30, statusColor, shadowColor);
			drawLine(view, 350, 100+(i-1)*30+24, 750, 100+(i-1)*30+25, bgColor, LINE_THIN);		
			currentMemoryInfo = (*currentMemoryInfo).next;
			i++;
		}

		showIntegerValue((*memoryManager).totalNum, 100, 100);

		(*view).refreshRectView(view);
	}
}

void showMemoryTable()
{
	View *mainView = (*testSheet).contentView;
	printMemoryTable(mainView);
}
