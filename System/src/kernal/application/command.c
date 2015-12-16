#include "../const/const.h"
#include "../type/type.h"
#include "../gui/resource.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/resource.h"
#include "../gui/sheet.h"
#include "../gui/image.h"
#include "../gui/view/view.h"
#include "../gui/graphics.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/view/imageButton.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "command.h"

extern Process *commandProcess;

static Sheet *winCommand;

static ImageButton *closeBtn;

static ImageButton *minizBtn;

static void onCloseBtnClick(ImageButton *this, MouseEvent *event);

static void onMinizBtnClick(ImageButton *this, MouseEvent *event);

static void commandApplicationMain();

static void prepareWindowSheetCmd();

void startCommandApplication()
{
	if (commandProcess==null) {
		commandProcess = requestProcess();
		(*commandProcess).tss.esp = allocPage(64 * 1024) + 64 * 1024;
		(*commandProcess).tss.eip = (int) &commandApplicationMain;
		(*commandProcess).tss.es = 2 * 8;
		(*commandProcess).tss.cs = 1 * 8;
		(*commandProcess).tss.ss = 2 * 8;
		(*commandProcess).tss.ds = 2 * 8;
		(*commandProcess).tss.fs = 2 * 8;
		(*commandProcess).tss.gs = 2 * 8;
		(*commandProcess).tss.cr3 = 0x60000;

		startRunProcess(commandProcess, 4);
	} else {
		if (winCommand!=null) {
			showWindowSheet(winCommand);
		}	
	}
}

static void commandApplicationMain()
{
	winCommand = prepareSheet();
    prepareWindowSheetCmd();
    loadWindowSheet(winCommand);
	(*commandProcess).mainWindow = winCommand;
	int count = 0;

	while(TRUE) {
		count++;
	}
}

static void prepareWindowSheetCmd()
{
    if (winCommand != null) {
        (*winCommand).x = 100;
        (*winCommand).y = 60;
        (*winCommand).width = 800;
        (*winCommand).height = 560;
        (*winCommand).buffer = (char *)allocPage((*winCommand).width*(*winCommand).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 800, 560);		
	
        resetSheet(winCommand);

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

		Color textColor;
        textColor.red = 0x55;
        textColor.green = 0x55;
        textColor.blue = 0x55;

		Color shadowColor;
        shadowColor.red = 0x55;
        shadowColor.green = 0x55;
        shadowColor.blue = 0x55;

		Color separateColor;
		separateColor.red = 50;
		separateColor.green = 60;
		separateColor.blue = 70;

		Color transparentColor;
		transparentColor.red = 0;
		transparentColor.green = 0;
		transparentColor.blue = 0;

		drawCornerRect(mainView, 0, 0, (*mainView).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 20, startColor, endColor, corner, DIRECTION_UP);
        drawRect(mainView, 1, 20, (*mainView).width-2, 21, separateColor);
		drawRect(mainView, 0, 21, (*mainView).width, 540, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 538, mainColor);

		printString(mainView, "Command", 7, 350, 4, textColor, shadowColor);

		Image *image = loadImageFromStorage(ico_btn_close);
		closeBtn = createImageButton(770, 1, 20, 20);
		(*closeBtn).initWithImage(closeBtn, image, transparentColor, transparentColor);
		(*closeBtn).onMouseClick = onCloseBtnClick;
		(*mainView).addSubView(mainView, (View *)closeBtn);
		(*image).release(image);

		image = loadImageFromStorage(ico_btn_miniz);
		minizBtn = createImageButton(750, 1, 20, 20);
		(*minizBtn).initWithImage(minizBtn, image, transparentColor, transparentColor);
		(*minizBtn).onMouseClick = onMinizBtnClick;
		(*mainView).addSubView(mainView, (View *)minizBtn);
		(*image).release(image);

		loadContentView(winCommand, mainView);
    }
}

static void onCloseBtnClick(ImageButton *this, MouseEvent *event)
{
	
}

static void onMinizBtnClick(ImageButton *this, MouseEvent *event)
{
	hideWindowSheet(winCommand);
}

