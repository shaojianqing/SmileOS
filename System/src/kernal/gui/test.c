#include "../const/const.h"
#include "../type/type.h"
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
        (*sheet).y = 100;
        (*sheet).width = 800;
        (*sheet).height = 500;
		(*sheet).buffer = (char *)allocPage(800*500*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 800, 500);

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
        drawRect(mainView, 0, 21, (*mainView).width, 479, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 477, mainColor);

		loadContentView(sheet, mainView);

        return sheet;
    }
}

void showIntegerValue(int value, int x, int y)
{
	Color mainColor;
    mainColor.red = 20;
    mainColor.green = 40;
    mainColor.blue = 60;

    Color color;
    color.red = 250;
    color.green = 88;
    color.blue = 22;

	View *mainView = (*testSheet).contentView;

    drawRect(mainView, x-20, y, 100, 20, mainColor);
    printHexInteger(mainView, value, x, y, color);
	(*mainView).refreshRectView(mainView);
}

void showBufferData(char *buffer)
{
	Color mainColor;
    mainColor.red = 240;
    mainColor.green = 200;
    mainColor.blue = 66;	
		
	int totalSize = 256, rowNum = 16, columnNum = 16;
	View *mainView = (*testSheet).contentView;

	int x=0,y=0;
	for (y=0;y<columnNum;++y) {
		for (x=0;x<rowNum;++x) {
			char data= *(buffer+y*16+x);
			printHexByte(mainView, data, x*28+340, y*28+44, mainColor);
		}	
	}

	(*mainView).refreshRectView(mainView);
}
