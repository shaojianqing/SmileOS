#include "../const/const.h"
#include "../type/type.h"
#include "view/view.h"
#include "sheet.h"
#include "color.h"
#include "image.h"
#include "view/startButton.h"
#include "desktop.h"

int currentDesktopIndex;

extern Process *kernelProcess;

Sheet *mouse;

Sheet *background;

Sheet *infoBarSheet;

Sheet *startBarSheet;

void initMouseSheet(Sheet *sheet);

void initInfoBarSheet(Sheet *sheet);

void initStartBarSheet(Sheet *sheet);

void initBackgroundSheet(Sheet *sheet);

Sheet* prepareInfoBarSheet(Sheet *sheet);

Sheet* prepareStartBarSheet(Sheet *sheet);

Sheet* prepareBackgroundSheet(Sheet *sheet);

void commandBtnOnMouseDown(View *this, MouseEvent *event);

void sysInfoBtnOnMouseDown(View *this, MouseEvent *event);

void imgInfoBtnOnMouseDown(View *this, MouseEvent *event);

void calculatorBtnOnMouseDown(View *this, MouseEvent *event);

void reArrangeDesktopSheet()
{
	initBackgroundSheet(background);
	initInfoBarSheet(infoBarSheet);
	initStartBarSheet(startBarSheet);	
	initMouseSheet(mouse);

	SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
	(*sheetManager).sheetNum = currentDesktopIndex+3;
}

void initDesktopInfoSheet()
{
	currentDesktopIndex = 1;	
	
	background = prepareSheet();
	(*background).process = kernelProcess;
    prepareBackgroundSheet(background);	  
    initBackgroundSheet(background);

	infoBarSheet = prepareSheet();
	initInfoBarSheet(infoBarSheet);
	(*infoBarSheet).process = kernelProcess;
	initInfoBarSheet(infoBarSheet);

	startBarSheet = prepareSheet();
	prepareStartBarSheet(startBarSheet);
	(*startBarSheet).process = kernelProcess;
	initStartBarSheet(startBarSheet);

    mouse = prepareSheet();
    prepareMouseSheet(mouse);
	(*mouse).process = kernelProcess;
	initMouseSheet(mouse);

	SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
	(*sheetManager).sheetNum = currentDesktopIndex+3;
	refreshSheetMap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    refreshSheetSub(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, currentDesktopIndex+2);
}

void initBackgroundSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		(*sheet).z = 0;
		(*sheetManager).sheets[0] = sheet;
	}
}

void initMouseSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		if (currentDesktopIndex+2<SHEET_NUM) {
			(*sheetManager).sheets[currentDesktopIndex+2] = sheet;
			(*sheet).z = currentDesktopIndex+2;
		}
	}
}

void initStartBarSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		if (currentDesktopIndex+1<SHEET_NUM) {
			(*sheetManager).sheets[currentDesktopIndex+1] = sheet;
			(*sheet).z = currentDesktopIndex+1;
		}
	}
}

void initInfoBarSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		if (currentDesktopIndex<SHEET_NUM) {
			(*sheetManager).sheets[currentDesktopIndex] = sheet;
			(*sheet).z = currentDesktopIndex;
		}
	}
}

Sheet* prepareBackgroundSheet(Sheet *sheet)
{
    if (sheet != 0) {
        (*sheet).x = 0;
        (*sheet).y = 0;
        (*sheet).width = SCREEN_WIDTH;
        (*sheet).height = SCREEN_HEIGHT;
		(*sheet).z = 0;
        u32 size = SCREEN_WIDTH*SCREEN_HEIGHT*SCREEN_DENSITY+8;
        Image *bgImage = loadImageFromStorage(0x4000);        
        (*sheet).buffer = (*bgImage).data;

        Color startColor;
        startColor.red = 250;
        startColor.green = 250;
        startColor.blue = 250;

        Color endColor;
        endColor.red = 220;
        endColor.green = 220;
        endColor.blue = 220;

        Color sepColor;
        sepColor.red = 240;
        sepColor.green = 240;
        sepColor.blue = 240;

        drawGradualVerticalRectAlphaInSheet(sheet, 0, 0, SCREEN_WIDTH, 24, startColor, endColor, 160);
        drawGradualVerticalTrapeziumInSheet(sheet, 62, 680, START_BAR_WIDTH, START_BAR_BG_HEIGHT -5, START_BAR_BG_HEIGHT -5, startColor, endColor, 200);
        drawRectAlphaInSheet(sheet, 62, 680+START_BAR_BG_HEIGHT -5, START_BAR_WIDTH, 1, sepColor, 240);
        drawRectAlphaInSheet(sheet, 62, 680+START_BAR_BG_HEIGHT -4, START_BAR_WIDTH, 4, endColor, 200);
    }
}

Sheet* prepareInfoBarSheet(Sheet *sheet)
{
    if (sheet!=null) {
        /*(*sheet).x = 0;
        (*sheet).y = 0;
        (*sheet).width = SCREEN_WIDTH;
        (*sheet).height = INFO_BAR_HEIGHT;
        (*sheet).buffer = (char *)allocMemoryInPage(SCREEN_WIDTH*INFO_BAR_HEIGHT*SCREEN_DENSITY);

        Color startColor;
        startColor.red = 250;
        startColor.green = 250;
        startColor.blue = 250;

        Color endColor;
        endColor.red = 220;
        endColor.green = 220;
        endColor.blue = 220;

        drawGradualVerticalRect((*sheet).buffer, sheet, 0, 0, SCREEN_WIDTH, INFO_BAR_HEIGHT, startColor, endColor);*/
    }
}

Sheet* prepareStartBarSheet(Sheet *sheet)
{
    if (sheet!=null) {		
		(*sheet).x = 62;
        (*sheet).y = 640;
        (*sheet).width = START_BAR_WIDTH;
        (*sheet).height = START_BAR_HEIGHT;
        (*sheet).buffer = (char *)allocMemoryInPage(START_BAR_WIDTH*START_BAR_HEIGHT*SCREEN_DENSITY);

		View *startBarConatiner = createView(0, 0, START_BAR_WIDTH, START_BAR_HEIGHT);

		StartButton *systemInfoBtn = createStartButton(740, 10, 80, 80, 0x8808);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)systemInfoBtn);
		(*systemInfoBtn).view.onMouseDown = sysInfoBtnOnMouseDown;

		StartButton *commandBtn = createStartButton(640, 10, 80, 80, 0x882e);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)commandBtn);
		(*commandBtn).view.onMouseDown = commandBtnOnMouseDown;

		StartButton *imageInfoBtn = createStartButton(540, 10, 80, 80, 0x8854);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)imageInfoBtn);
		(*imageInfoBtn).view.onMouseDown = imgInfoBtnOnMouseDown;

		StartButton *calculatorBtn = createStartButton(440, 10, 80, 80, 0x887a);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)calculatorBtn);
		(*calculatorBtn).view.onMouseDown = calculatorBtnOnMouseDown;

		loadContentView(sheet, startBarConatiner);	
    }
}

void sysInfoBtnOnMouseDown(View *this, MouseEvent *event)
{	
	//showIntegerValue(88, 100, 100);
	//startSysInfoApplication();
}

void commandBtnOnMouseDown(View *this, MouseEvent *event)
{
	//showIntegerValue(66, 100, 100);
	//startCommandApplication();
}

void imgInfoBtnOnMouseDown(View *this, MouseEvent *event)
{
	startMathematicsApplication();
}

void calculatorBtnOnMouseDown(View *this, MouseEvent *event)
{
	startCalculatorApplication();
	//startMathematicsApplication();
}
