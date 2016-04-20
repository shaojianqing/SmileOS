#include "../const/const.h"
#include "../type/type.h"
#include "resource.h"
#include "sheet.h"
#include "color.h"
#include "image.h"
#include "view/view.h"
#include "view/startButton.h"
#include "view/imageButton.h"
#include "../execute/execute.h"
#include "../execute/application.h"
#include "desktop.h"
#include "charset.h"
#include "test.h"

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

Sheet* prepareBackgroundSheet(Sheet *sheet, u32 bgCode);

void commandBtnOnMouseDown(View *this, MouseEvent *event);

void sysInfoBtnOnMouseDown(View *this, MouseEvent *event);

void imgInfoBtnOnMouseDown(View *this, MouseEvent *event);

void calculatorBtnOnMouseDown(View *this, MouseEvent *event);

void dataGraphBtnOnMouseDown(View *this, MouseEvent *event);

void mathmaticsBtnOnMouseDown(View *this, MouseEvent *event);

void startLoadExecuteFile();

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
    prepareBackgroundSheet(background, bg_1);	  
    initBackgroundSheet(background);

	infoBarSheet = prepareSheet();
	prepareInfoBarSheet(infoBarSheet);
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

void setBackground(u32 bgCode)
{
	prepareBackgroundSheet(background, bgCode);
	refreshSheetMap(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    refreshSheetSub(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1);	
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

Sheet* prepareBackgroundSheet(Sheet *sheet, u32 bgCode)
{
    if (sheet != 0) {
        (*sheet).x = 0;
        (*sheet).y = 0;
        (*sheet).width = SCREEN_WIDTH;
        (*sheet).height = SCREEN_HEIGHT;
		(*sheet).z = 0;
        u32 size = SCREEN_WIDTH*SCREEN_HEIGHT*SCREEN_DENSITY;
		(*sheet).buffer  = (u8 *)allocPage(size);
        Image *bgImage = loadImageFromStorage(bgCode);	 
		drawBackround(sheet, bgImage);
		//(*bgImage).release(bgImage);	
	
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
        drawGradualVerticalTrapeziumInSheet(sheet, 112, 680, START_BAR_WIDTH, START_BAR_BG_HEIGHT -5, START_BAR_BG_HEIGHT -5, startColor, endColor, 200);
        drawRectAlphaInSheet(sheet, 112, 680 + START_BAR_BG_HEIGHT -5, START_BAR_WIDTH, 1, sepColor, 240);
        drawRectAlphaInSheet(sheet, 112, 680 + START_BAR_BG_HEIGHT -4, START_BAR_WIDTH, 4, endColor, 200);
    }
}

Sheet* prepareInfoBarSheet(Sheet *sheet)
{
    if (sheet!=null) {
        (*sheet).x = 0;
        (*sheet).y = 0;
        (*sheet).width = SCREEN_WIDTH;
        (*sheet).height = INFO_BAR_HEIGHT;
        (*sheet).buffer = (u8 *)allocPage(SCREEN_WIDTH*INFO_BAR_HEIGHT*SCREEN_DENSITY);

		Color normalColor;
		normalColor.red = TRANSPARENT;
		normalColor.green = TRANSPARENT;
		normalColor.blue = TRANSPARENT;

		Color selectColor;
		selectColor.red = TRANSPARENT;
		selectColor.green = TRANSPARENT;
		selectColor.blue = TRANSPARENT;

		Color textColor;
        textColor.red = 0x55;
        textColor.green = 0x55;
        textColor.blue = 0x55;

		Color shadowColor;
        shadowColor.red = 0x55;
        shadowColor.green = 0x55;
        shadowColor.blue = 0x55;	

		View *infoBarConatiner = createView(0, 0, SCREEN_WIDTH, INFO_BAR_HEIGHT);
		(*infoBarConatiner).clearView(infoBarConatiner);

		Image *image = loadImageFromStorage(ico_sys_logo);
		ImageButton *logoImgBtn = createImageButton(0, 0, 100, 24);
		(*logoImgBtn).initWithImage(logoImgBtn, image, normalColor, selectColor);
		(*image).release(image);

		image = loadImageFromStorage(ico_sys_power);
		ImageButton *powerImgBtn = createImageButton(800, 0, 60, 24);
		(*powerImgBtn).initWithImage(powerImgBtn, image, normalColor, selectColor);
		(*image).release(image);

		image = loadImageFromStorage(ico_sys_network);
		ImageButton *networkImgBtn = createImageButton(750, 0, 32, 24);
		(*networkImgBtn).initWithImage(networkImgBtn, image, normalColor, selectColor);
		(*image).release(image);

		printString(infoBarConatiner, "Shaojianqing", 12, 900, 4, textColor, shadowColor);	

		(*infoBarConatiner).addSubView(infoBarConatiner, (View *)logoImgBtn);
		(*infoBarConatiner).addSubView(infoBarConatiner, (View *)powerImgBtn);
		(*infoBarConatiner).addSubView(infoBarConatiner, (View *)networkImgBtn);
		
		loadContentView(sheet, infoBarConatiner);
    }
}

Sheet* prepareStartBarSheet(Sheet *sheet)
{
    if (sheet!=null) {		
		(*sheet).x = 112;
        (*sheet).y = 640;
        (*sheet).width = START_BAR_WIDTH;
        (*sheet).height = START_BAR_HEIGHT;
        (*sheet).buffer = (u8 *)allocPage(START_BAR_WIDTH*START_BAR_HEIGHT*SCREEN_DENSITY);

		View *startBarConatiner = createView(0, 0, START_BAR_WIDTH, START_BAR_HEIGHT);

		StartButton *systemInfoBtn = createStartButton(610, 10, 80, 80, ico_app_sys);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)systemInfoBtn);
		(*systemInfoBtn).view.onMouseDown = sysInfoBtnOnMouseDown;

		StartButton *commandBtn = createStartButton(510, 10, 80, 80, ico_app_cmd);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)commandBtn);
		(*commandBtn).view.onMouseDown = commandBtnOnMouseDown;

		StartButton *imageInfoBtn = createStartButton(410, 10, 80, 80, ico_app_img);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)imageInfoBtn);
		(*imageInfoBtn).view.onMouseDown = imgInfoBtnOnMouseDown;

		StartButton *calculatorBtn = createStartButton(310, 10, 80, 80, ico_app_cal);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)calculatorBtn);
		(*calculatorBtn).view.onMouseDown = calculatorBtnOnMouseDown;

		StartButton *graphDataBtn = createStartButton(210, 10, 80, 80, ico_app_grh);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)graphDataBtn);
		(*graphDataBtn).view.onMouseDown = dataGraphBtnOnMouseDown;

		StartButton *mathmaticsBtn = createStartButton(110, 10, 80, 80, ico_app_mat);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)mathmaticsBtn);
		(*mathmaticsBtn).view.onMouseDown = mathmaticsBtnOnMouseDown;

		loadContentView(sheet, startBarConatiner);	
    }
}

void sysInfoBtnOnMouseDown(View *this, MouseEvent *event)
{
	startSysInfoApplication();
}

void commandBtnOnMouseDown(View *this, MouseEvent *event)
{
	startCommandApplication();
}

void imgInfoBtnOnMouseDown(View *this, MouseEvent *event)
{	
	startImageViewerApplication();
}

void calculatorBtnOnMouseDown(View *this, MouseEvent *event)
{
	startCalculatorApplication();
}

void dataGraphBtnOnMouseDown(View *this, MouseEvent *event)
{
	startDataGraphApplication();
}

void mathmaticsBtnOnMouseDown(View *this, MouseEvent *event)
{
	startMathematicsApplication();
}

void startLoadExecuteFile()
{		
	ExecutableFile *executeFile = loadExecuteFromStorage(0x1000);
	Application *application = createApplication(executeFile);
	if (application!=null) {
		startApplication(application);
	}	
}
