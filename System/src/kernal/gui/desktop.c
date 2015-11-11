#include "../const/const.h"
#include "../type/type.h"
#include "view/view.h"
#include "sheet.h"
#include "color.h"
#include "image.h"
#include "view/startButton.h"
#include "../execute/execute.h"
#include "../execute/application.h"
#include "desktop.h"
#include "test.h"

//u8 *buf0, *buf1, *buf2, *buf3;

bool oper = TRUE;

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

void dataGraphBtnOnMouseDown(View *this, MouseEvent *event);

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

	oper = TRUE;
	
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
        (*sheet).buffer = (char *)allocPage(START_BAR_WIDTH*START_BAR_HEIGHT*SCREEN_DENSITY);

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

		StartButton *graphDataBtn = createStartButton(340, 10, 80, 80, 0x88a0);
		(*startBarConatiner).addSubView(startBarConatiner, (View *)graphDataBtn);
		(*graphDataBtn).view.onMouseDown = dataGraphBtnOnMouseDown;

		loadContentView(sheet, startBarConatiner);	
    }
}

void sysInfoBtnOnMouseDown(View *this, MouseEvent *event)
{
	if (oper==TRUE) {
		oper = FALSE;
		/*u32 *buf0 = (u32 *)alloc(0x08);	
		u32 *buf1 = (u32 *)alloc(0x13);
		u32 *buf2 = (u32 *)alloc(0x23);
		u32 *buf3 = (u32 *)alloc(0x31);
		u32 *buf4 = (u32 *)alloc(0x101);
		u32 *buf5 = (u32 *)alloc(0x41);
		u32 *buf6 = (u32 *)alloc(0x51);
		u32 *buf7 = (u32 *)alloc(0x29);
		u32 *buf8 = (u32 *)alloc(0x39);
		//u32 *buf9 = (u32 *)alloc(0x43);//-------------------------------
		//u32 *buf10 = (u32 *)alloc(0x47);
		//u32 *buf11 = (u32 *)alloc(0x53);
		//u32 *buf12 = (u32 *)alloc(0x61);

		release(buf0);
		//release(buf1);
		release(buf2);
		release(buf3);
		//release(buf4);
		release(buf5);
		//release(buf6);
		release(buf7);
		//release(buf8);
		//release(buf6);
		release(buf8);
		//release(buf10);

		u32 *buf11 = (u32 *)alloc(0x29);*/

		//u32 *buf13 = (u32 *)alloc(0x103);

		//release((u32)buf9);
		//release((u32)buf1);
		/*u32 *buf0 = (u32 *)alloc(0x08);
		u32 *buf4 = (u32 *)alloc(0x101);
		u32 *buf5 = (u32 *)alloc(0x41);

		*/	
	
		//release((u32)buf2);
		//release((u32)buf3);
		//release((u32)buf1);
		//release((u32)buf2);
		//release((u32)buf1);
		//release((u32)buf0);
		//release((u32)buf0);
	
		showMemoryTable();
	}

	//showIntegerValue(88, 100, 100);
	//startLoadExecuteFile();
	//startSysInfoApplication();
}

void commandBtnOnMouseDown(View *this, MouseEvent *event)
{
	/*if (buf2!=null) {
		showIntegerValue((u32)buf2, 100, 60);
		release((u32)buf2);
		buf2=null;
	}*/
	
	showMemoryTable();
	//showIntegerValue(111, 100, 100);
	//startCommandApplication();
}

void imgInfoBtnOnMouseDown(View *this, MouseEvent *event)
{
	//buf3 = (u8 *)alloc(0x13);
	//showMemoryTable();
	
	startMathematicsApplication();
}

void calculatorBtnOnMouseDown(View *this, MouseEvent *event)
{
	//showIntegerValue(88, 100, 100);
	startCalculatorApplication();
}

void dataGraphBtnOnMouseDown(View *this, MouseEvent *event)
{
	//showIntegerValue(33, 100, 100);
	startDataGraphApplication();
}

void startLoadExecuteFile()
{
	

	/*u8 *buf1 = (u8 *)alloc(0x31);
	showIntegerValue((u32)buf1, 100, 160);

	//

	u8 *buf2 = (u8 *)alloc(0x04);
	showIntegerValue((u32)buf2, 100, 220);*/

	

	//release((u32)buf1);

	//release((u32)buf2);

	//buf0 = (u8 *)alloc(0x08);

	/*release((u32)buf1);

	release((u32)buf0);

	release((u32)buf2);
	
	u8 *buf4 = (u8 *)alloc(0x08);
	showIntegerValue((u32)buf4, 200, 280);

	u8 *buf5 = (u8 *)alloc(0x06);
	showIntegerValue((u32)buf5, 200, 340);

	release((int)buf4);


	u8 *buf6 = (u8 *)alloc(0x09);
	showIntegerValue((u32)buf6, 200, 400);

	release((u32)buf5);

	release((u32)buf6);*/

	/*ExecutableFile *executeFile = loadExecuteFromStorage(0x1000);
	Application *application = createApplication(executeFile);
	if (application!=null) {
		startApplication(application);
	}

	showBufferData((*executeFile).executeBuffer+0x1110);
	ElfFileHeader *header = (*executeFile).header;
	ElfProgramHeader *programHeader = (*executeFile).dataHeader;
	showIntegerValue((*executeFile).executeSize, 100, 300);*/
}
