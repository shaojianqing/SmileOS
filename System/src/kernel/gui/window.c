#include "../type/type.h"
#include "color.h"
#include "sheet.h"
#include "corner.h"
#include "window.h"

void showInfo(Sheet *sheet, int x, int y, int key)
{
    Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;

	Color shadowColor;
    shadowColor.red = 30;
    shadowColor.green = 30;
    shadowColor.blue = 30;

    Color color;
    color.red = 240;
    color.green = 240;
    color.blue = 240;

    drawRect((*sheet).buffer, sheet, x, y, 100, 50, color);
    printInteger(sheet, key, x, y, mainColor, shadowColor);
    refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}

void showString(Sheet *sheet, int x, int y, char *string, int size) 
{
	Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;

	Color shadowColor;
    shadowColor.red = 30;
    shadowColor.green = 30;
    shadowColor.blue = 30;

	printString(sheet, string, size, x, y, mainColor, shadowColor);	
	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}

void showBufferInfo(Sheet *sheet, char *buffer)
{
	Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;

	Color shadowColor;
    shadowColor.red = 30;
    shadowColor.green = 30;
    shadowColor.blue = 30;
		
	int totalSize = 256, rowNum = 16, columnNum = 16;

	int x=0,y=0;
	for (y=0;y<columnNum;++y) {
		for (x=0;x<rowNum;++x) {
			char data= *(buffer+y*16+x);
			printHexByte(sheet, data, x*28+90, y*28+32, mainColor, shadowColor);
		}	
	}

	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}
