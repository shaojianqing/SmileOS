#include "../type/type.h"
#include "color.h"
#include "sheet.h"
#include "corner.h"
#include "window.h"

Sheet* prepareWindowSheetOne(Sheet *sheet)
{
    if (sheet != 0) {
        (*sheet).x = 100;
        (*sheet).y = 100;
        (*sheet).width = 300;
        (*sheet).height = 200;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);

        resetSheet(sheet);

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
        mainColor.red = 220;
        mainColor.green = 220;
        mainColor.blue = 220;

		Color txtBorderColor;
        txtBorderColor.red = 160;
        txtBorderColor.green = 160;
        txtBorderColor.blue = 160;		

        drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-2, 20, startColor, endColor, corner);
        drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 179, mainBgColor);
        drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-2, 178, mainColor);

        return sheet;
    }
}

Sheet* prepareWindowSheetTwo(Sheet *sheet)
{
	if (sheet != 0) {
        (*sheet).x = 624;
        (*sheet).y = 100;
        (*sheet).width = 300;
        (*sheet).height = 200;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);

        resetSheet(sheet);

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
        mainColor.red = 220;
        mainColor.green = 220;
        mainColor.blue = 220;

		Color txtBorderColor;
        txtBorderColor.red = 160;
        txtBorderColor.green = 160;
        txtBorderColor.blue = 160;		

        drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-2, 20, startColor, endColor, corner);
        drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 179, mainBgColor);
        drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-2, 178, mainColor);

        return sheet;
    }
}

Sheet* prepareWindowSheetThree(Sheet *sheet)
{
	if (sheet != 0) {
        (*sheet).x = 100;
        (*sheet).y = 400;
        (*sheet).width = 300;
        (*sheet).height = 200;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);

        resetSheet(sheet);

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
        mainColor.red = 220;
        mainColor.green = 220;
        mainColor.blue = 220;

		Color txtBorderColor;
        txtBorderColor.red = 160;
        txtBorderColor.green = 160;
        txtBorderColor.blue = 160;		

        drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-2, 20, startColor, endColor, corner);
        drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 179, mainBgColor);
        drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-2, 178, mainColor);

        return sheet;
    }
}

Sheet* prepareWindowSheetFour(Sheet *sheet)
{
	if (sheet != 0) {
        (*sheet).x = 624;
        (*sheet).y = 400;
        (*sheet).width = 300;
        (*sheet).height = 200;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);

        resetSheet(sheet);

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
        mainColor.red = 220;
        mainColor.green = 220;
        mainColor.blue = 220;

		Color txtBorderColor;
        txtBorderColor.red = 160;
        txtBorderColor.green = 160;
        txtBorderColor.blue = 160;		

        drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-2, 20, startColor, endColor, corner);
        drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 179, mainBgColor);
        drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-2, 178, mainColor);

        return sheet;
    }
}

void showInfo(Sheet *sheet, int x, int y, int key)
{
    Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;

    Color color;
    color.red = 240;
    color.green = 240;
    color.blue = 240;

    drawRect((*sheet).buffer, sheet, x, y, 100, 50, color);
    printInteger(sheet, key, x, y, mainColor);
    refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}

void showString(Sheet *sheet, int x, int y, char *string, int size) {
	Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;

	printString(sheet, string, size, x, y, mainColor);	
	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}

void showBufferInfo(Sheet *sheet, char *buffer)
{
	Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;	
		
	int totalSize = 256, rowNum = 16, columnNum = 16;

	int x=0,y=0;
	for (y=0;y<columnNum;++y) {
		for (x=0;x<rowNum;++x) {
			char data= *(buffer+y*16+x);
			printHexByte(sheet, data, x*28+90, y*28+32, mainColor);
		}	
	}

	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}


