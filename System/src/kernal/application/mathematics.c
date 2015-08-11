#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/coorPanel.h"
#include "../process/process.h"
#include "command.h"

extern Process *mathematicsProcess;

Button *lineBtn;

Button *circleBtn;

Factory mathematicsFactory;

void onLineBtnClick(Button *this, MouseEvent *event);

void onCircleBtnClick(Button *this, MouseEvent *event);

void mathematicsApplicationMain();

void prepareWindowSheetMath(Sheet *sheet);

void mathematicsOnTimer()
{
	mathematicsFactory.changeButtonStatus(&mathematicsFactory);
}

void startMathematicsApplication()
{
	if (mathematicsProcess==null) {
		mathematicsProcess = requestProcess();
		(*mathematicsProcess).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
		(*mathematicsProcess).tss.eip = (int) &mathematicsApplicationMain;
		(*mathematicsProcess).tss.es = 2 * 8;
		(*mathematicsProcess).tss.cs = 1 * 8;
		(*mathematicsProcess).tss.ss = 2 * 8;
		(*mathematicsProcess).tss.ds = 2 * 8;
		(*mathematicsProcess).tss.fs = 2 * 8;
		(*mathematicsProcess).tss.gs = 2 * 8;
		startRunProcess(mathematicsProcess, 1, 4);
	}
}

void mathematicsApplicationMain()
{
	initFactory(&mathematicsFactory, mathematicsOnTimer);
	
	Sheet *winMathematics = prepareSheet();
    prepareWindowSheetMath(winMathematics);
    loadWindowSheet(winMathematics);
	(*mathematicsProcess).mainWindow = winMathematics;

	while(TRUE) {
		mathematicsFactory.deselectButton(&mathematicsFactory);
		mathematicsFactory.doProcessEvent(&mathematicsFactory);
	}
}

void prepareWindowSheetMath(Sheet *sheet)
{
    if (sheet != null) {
        (*sheet).x = 80;
        (*sheet).y = 80;
        (*sheet).width = 800;
        (*sheet).height = 560;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 800, 560);

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
        mainColor.red = 210;
        mainColor.green = 210;
        mainColor.blue = 210;

		Color textColor;
        textColor.red = 0x55;
        textColor.green = 0x55;
        textColor.blue = 0x55;

        drawCornerRect(mainView, 0, 0, (*mainView).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 20, startColor, endColor, corner, DIRECTION_UP);
        drawRect(mainView, 0, 21, (*mainView).width, 540, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 538, mainColor);

		printString(mainView, "Mathematics", 12, 350, 4, textColor);

		CoorPanel *coorPanel = createCoorPanel(5, 60, 790, 494);
		(*mainView).addSubView(mainView, (View *)coorPanel);

		lineBtn = createButton(5, 24, 100, 32, &mathematicsFactory);
		(*lineBtn).initButton(lineBtn, "Line", 4, ButtonStyleLightGray);
		(*lineBtn).onMouseClick = onLineBtnClick;
		(*mainView).addSubView(mainView, (View *)lineBtn);

		circleBtn = createButton(110, 24, 100, 32, &mathematicsFactory);
		(*circleBtn).initButton(circleBtn, "Circle", 6, ButtonStyleLightGray);
		(*circleBtn).onMouseClick = onCircleBtnClick;
		(*mainView).addSubView(mainView, (View *)circleBtn);

		loadContentView(sheet, mainView);	
    }
}

void onLineBtnClick(Button *this, MouseEvent *event)
{
	int a = -89;
	int b = 100;
	int c = a+b;
	showIntegerValue(c, 100, 50);
}

void onCircleBtnClick(Button *this, MouseEvent *event)
{
	showIntegerValue(3663, 100, 50);
}


