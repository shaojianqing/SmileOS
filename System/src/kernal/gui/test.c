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
        (*sheet).x = 10;
        (*sheet).y = 100;
        (*sheet).width = 180;
        (*sheet).height = 200;
		(*sheet).buffer = (char *)allocMemoryInPage(300*200*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 180, 200);

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
        drawRect(mainView, 0, 21, (*mainView).width, 179, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 177, mainColor);

		loadContentView(sheet, mainView);

        //drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        //drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-2, 20, startColor, endColor, corner);
        //drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 179, mainBgColor);
        //drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-2, 178, mainColor);

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
    color.red = 240;
    color.green = 240;
    color.blue = 240;

	View *mainView = (*testSheet).contentView;

    drawRect(mainView, x-20, y, 100, 20, mainColor);
    printInteger(mainView, value, x, y, color);
	(*mainView).refreshRectView(mainView);
	
}
