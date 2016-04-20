#include "../const/const.h"
#include "../type/type.h"
#include "../gui/resource.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../gui/image.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/imageButton.h"
#include "../gui/view/item/headerItem.h"
#include "../gui/view/item/gridDataItem.h"
#include "../gui/view/gridPanel.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "data/processData.h"
#include "systemInfo.h"

extern Process *sysInfoProcess;

static Sheet *winSysInfo;

static ImageButton *closeBtn;

static ImageButton *minizBtn;

static Factory sysInfoFactory;

static Button *processInfoBtn;

static Button *memoryInfoBtn;

static HeaderItem headerItemList[5];

static ProcessData processDataList[10];

static GridPanel *processDataGrid;

static void prepareProcessHeaderList();

static void prepareProcessDataList();

static void sysInfoApplicationMain();

static void prepareWindowSheetSys();

static GridDataItem *processItemRender(GridPanel *this, u32 index, int width, int height);

static void onCloseBtnClick(ImageButton *this, MouseEvent *event);

static void onMinizBtnClick(ImageButton *this, MouseEvent *event);

static void onProcessBtnClick(Button *this, MouseEvent *event);

static void onMemoryBtnClick(Button *this, MouseEvent *event);

static void sysInfoOnTimer()
{
	sysInfoFactory.changeButtonStatus(&sysInfoFactory);
}

void startSysInfoApplication()
{
	if (sysInfoProcess==null) {
		sysInfoProcess = requestProcess();
		(*sysInfoProcess).tss.esp = allocPage(64 * 1024) + 64 * 1024;
		(*sysInfoProcess).tss.eip = (int) &sysInfoApplicationMain;
		(*sysInfoProcess).tss.es = 2 * 8;
		(*sysInfoProcess).tss.cs = 1 * 8;
		(*sysInfoProcess).tss.ss = 2 * 8;
		(*sysInfoProcess).tss.ds = 2 * 8;
		(*sysInfoProcess).tss.fs = 2 * 8;
		(*sysInfoProcess).tss.gs = 2 * 8;
		(*sysInfoProcess).tss.cr3 = 0x60000;

		startRunProcess(sysInfoProcess, 4);
	} else {
		if (winSysInfo!=null && (*winSysInfo).visible==FALSE) {
			showWindowSheet(winSysInfo);
		}		
	}
}

static void sysInfoApplicationMain()
{
	initFactory(&sysInfoFactory, sysInfoOnTimer);
	
	winSysInfo = prepareSheet();
    prepareWindowSheetSys();
    loadWindowSheet(winSysInfo);
	(*sysInfoProcess).mainWindow = winSysInfo;

	while(TRUE) {
		sysInfoFactory.deselectButton(&sysInfoFactory);
		sysInfoFactory.doProcessEvent(&sysInfoFactory);
	}
}

static void prepareWindowSheetSys(Sheet *sheet)
{
    if (winSysInfo != null) {
        (*winSysInfo).x = 460;
        (*winSysInfo).y = 50;
        (*winSysInfo).width = 500;
        (*winSysInfo).height = 560;
        (*winSysInfo).buffer = (u8 *)allocPage((*winSysInfo).width*(*winSysInfo).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 500, 560);

		resetSheet(winSysInfo);

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

		Color shadowColor;
        shadowColor.red = 0x55;
        shadowColor.green = 0x55;
        shadowColor.blue = 0x55;

		Color borderColor;
        borderColor.red = 160;
        borderColor.green = 160;
        borderColor.blue = 160;

		Color contentColor;
        contentColor.red = 250;
        contentColor.green = 250;
        contentColor.blue = 250;

		Color transparentColor;
		transparentColor.red = 0;
		transparentColor.green = 0;
		transparentColor.blue = 0;

        drawCornerRect(mainView, 0, 0, (*mainView).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 20, startColor, endColor, corner, DIRECTION_UP);
        drawRect(mainView, 0, 21, (*mainView).width, 540, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 538, mainColor);

		printString(mainView, "System Infomation", 18, 180, 4, textColor, shadowColor);

		Image *image = loadImageFromStorage(ico_btn_close);
		closeBtn = createImageButton(470, 1, 20, 20);
		(*closeBtn).initWithImage(closeBtn, image, transparentColor, transparentColor);
		(*closeBtn).onMouseClick = onCloseBtnClick;
		(*mainView).addSubView(mainView, (View *)closeBtn);
		(*image).release(image);

		image = loadImageFromStorage(ico_btn_miniz);
		minizBtn = createImageButton(450, 1, 20, 20);
		(*minizBtn).initWithImage(minizBtn, image, transparentColor, transparentColor);
		(*minizBtn).onMouseClick = onMinizBtnClick;
		(*mainView).addSubView(mainView, (View *)minizBtn);
		(*image).release(image);

		Image *processIco = (Image *)loadImageFromStorage(ico_btn_sys_process);
		processInfoBtn = createButton(5, 24, 150, 32, &sysInfoFactory, processIco);
		(*processInfoBtn).initButton(processInfoBtn, "Process Info", 12, ButtonStyleLightGray);
		(*processInfoBtn).onMouseClick = onProcessBtnClick;
		(*mainView).addSubView(mainView, (View *)processInfoBtn);
		(*processIco).release(processIco);

		Image *memoryIco = (Image *)loadImageFromStorage(ico_btn_sys_memory);
		memoryInfoBtn = createButton(160, 24, 150, 32, &sysInfoFactory, memoryIco);
		(*memoryInfoBtn).initButton(memoryInfoBtn, "Memory Info", 11, ButtonStyleLightGray);
		(*memoryInfoBtn).onMouseClick = onMemoryBtnClick;
		(*mainView).addSubView(mainView, (View *)memoryInfoBtn);
		(*memoryIco).release(memoryIco);

		prepareProcessHeaderList();
		prepareProcessDataList();

		processDataGrid = createGridPanel(5, 60, 490, 495);
		(*processDataGrid).initPanel(processDataGrid, headerItemList, 5);
		(*processDataGrid).renderDataGrid(processDataGrid, 10, processItemRender);
		(*mainView).addSubView(mainView, (View *)processDataGrid);

		loadContentView(winSysInfo, mainView);
    }
}

static GridDataItem *processItemRender(GridPanel *this, u32 index, int width, int height)
{
	Color textColor;
    textColor.red = 0x55;
    textColor.green = 0x55;
    textColor.blue = 0x55;

	Color separateColor;
    separateColor.red = 160;
    separateColor.green = 160;
    separateColor.blue = 160;

	Color backgroundColor;
    backgroundColor.red = 230;
    backgroundColor.green = 230;
    backgroundColor.blue = 250;

	Color systemColor;
	systemColor.red = 180;
	systemColor.green = 80;
	systemColor.blue = 60;

	Color userColor;
	userColor.red = 160;
	userColor.green = 160;
	userColor.blue = 20;

	Color runningColor;
	runningColor.red = 40;
	runningColor.green = 180;
	runningColor.blue = 40;

	Color blockedColor;
	blockedColor.red = 180;
	blockedColor.green = 40;
	blockedColor.blue = 40;

	Color readyColor;
	readyColor.red = 180;
	readyColor.green = 180;
	readyColor.blue = 20;
	
	if (this != null) {
		int width = (*this).view.width;
		ProcessData *processData = processDataList+index;
		GridDataItem *gridDataItem = createGridDataItem(width, GRID_DATA_ITEM_HEIGHT);

		if (index%2!=0) {
			drawRect((View *)gridDataItem, 1, 0, width-2, GRID_DATA_ITEM_HEIGHT, backgroundColor);
		}

		printInteger((View *)gridDataItem, (*processData).pId, 20, 6, textColor, textColor);
		printString((View *)gridDataItem, (*processData).name, (*processData).wordCount, 
					70, 6, textColor, textColor);
		
		if ((*processData).type==TYPE_PROCESS_SYSS) {
			printString((View *)gridDataItem, "System", 6, 230, 6, systemColor, systemColor);
		} else if ((*processData).type==TYPE_PROCESS_USER) {
			printString((View *)gridDataItem, "User", 4, 230, 6, userColor, userColor);
 		}

		if ((*processData).status==SIGN_PROCESS_RUNNING) {
			printString((View *)gridDataItem, "Running", 7, 310, 6, runningColor, runningColor);
		} else if ((*processData).status==SIGN_PROCESS_BLOCKED) {
			printString((View *)gridDataItem, "Blocked", 7, 310, 6, blockedColor, blockedColor);
 		} else if ((*processData).status==SIGN_PROCESS_READY) {
			printString((View *)gridDataItem, "Ready", 5, 310, 6, readyColor, readyColor);
 		}

		printInteger((View *)gridDataItem, (*processData).priority, 420, 6, textColor, textColor);

		drawLine((View *)gridDataItem, 60, 0, 60, 32, separateColor, LINE_THIN);
		drawLine((View *)gridDataItem, 220, 0, 220, 32, separateColor, LINE_THIN);
		drawLine((View *)gridDataItem, 300, 0, 300, 32, separateColor, LINE_THIN);
		drawLine((View *)gridDataItem, 380, 0, 380, 32, separateColor, LINE_THIN);
		drawLine((View *)gridDataItem, 460, 0, 460, 32, separateColor, LINE_THIN);
		drawLine((View *)gridDataItem, 0, 31, width, 31, separateColor, LINE_THIN);
		return gridDataItem;
	}
	return null;
}

static void prepareProcessHeaderList()
{
	HeaderItem *headerItem = headerItemList;
	(*headerItem).name = "PID";
	(*headerItem).wordCount = 3;
	(*headerItem).width = 60;

	headerItem = headerItemList+1;
	(*headerItem).name = "Name";
	(*headerItem).wordCount = 4;
	(*headerItem).width = 160;

	headerItem = headerItemList+2;
	(*headerItem).name = "Type";
	(*headerItem).wordCount = 4;
	(*headerItem).width = 80;

	headerItem = headerItemList+3;
	(*headerItem).name = "Status";
	(*headerItem).wordCount = 6;
	(*headerItem).width = 80;

	headerItem = headerItemList+4;
	(*headerItem).name = "Priority";
	(*headerItem).wordCount = 8;
	(*headerItem).width = 80;
}

static void prepareProcessDataList()
{
	ProcessData *processData = processDataList;
	(*processData).name = "System Kernal";
	(*processData).wordCount = 13;
	(*processData).type = TYPE_PROCESS_SYSS;
	(*processData).status = SIGN_PROCESS_RUNNING;
	(*processData).priority = 1;
	(*processData).pId = 22;

	processData = processDataList+1;
	(*processData).name = "Calculator";
	(*processData).type = TYPE_PROCESS_USER;
	(*processData).status = SIGN_PROCESS_BLOCKED;
	(*processData).wordCount = 10;
	(*processData).priority = 4;
	(*processData).pId = 21;

	processData = processDataList+2;
	(*processData).name = "Mathmatics";
	(*processData).type = TYPE_PROCESS_USER;
	(*processData).status = SIGN_PROCESS_BLOCKED;
	(*processData).wordCount = 10;
	(*processData).priority = 4;
	(*processData).pId = 18;

	processData = processDataList+3;
	(*processData).name = "DataGraph";
	(*processData).type = TYPE_PROCESS_USER;
	(*processData).status = SIGN_PROCESS_READY;
	(*processData).wordCount = 9;
	(*processData).priority = 4;
	(*processData).pId = 88;

	processData = processDataList+4;
	(*processData).name = "System Info";
	(*processData).type = TYPE_PROCESS_USER;
	(*processData).status = SIGN_PROCESS_BLOCKED;
	(*processData).wordCount = 11;
	(*processData).priority = 4;
	(*processData).pId = 32;

	processData = processDataList+5;
	(*processData).name = "Statistics";
	(*processData).type = TYPE_PROCESS_SYSS;
	(*processData).status = SIGN_PROCESS_BLOCKED;
	(*processData).wordCount = 10;
	(*processData).priority = 2;
	(*processData).pId = 36;

	processData = processDataList+6;
	(*processData).name = "Web Services";
	(*processData).type = TYPE_PROCESS_SYSS;
	(*processData).status = SIGN_PROCESS_READY;
	(*processData).wordCount = 12;
	(*processData).priority = 3;
	(*processData).pId = 51;

	processData = processDataList+7;
	(*processData).name = "Connector";
	(*processData).type = TYPE_PROCESS_USER;
	(*processData).status = SIGN_PROCESS_BLOCKED;
	(*processData).wordCount = 9;
	(*processData).priority = 4;
	(*processData).pId = 66;

	processData = processDataList+8;
	(*processData).name = "Telnet Client";
	(*processData).type = TYPE_PROCESS_USER;
	(*processData).status = SIGN_PROCESS_READY;
	(*processData).wordCount = 13;
	(*processData).priority = 3;
	(*processData).pId = 88;

	processData = processDataList+9;
	(*processData).name = "DataBase Services";
	(*processData).type = TYPE_PROCESS_SYSS;
	(*processData).status = SIGN_PROCESS_BLOCKED;
	(*processData).wordCount = 17;
	(*processData).priority = 2;
	(*processData).pId = 72;
}

static void onProcessBtnClick(Button *this, MouseEvent *event)
{
	
}

static void onMemoryBtnClick(Button *this, MouseEvent *event)
{
	
}

static void onCloseBtnClick(ImageButton *this, MouseEvent *event)
{
	
}

static void onMinizBtnClick(ImageButton *this, MouseEvent *event)
{
	hideWindowSheet(winSysInfo);
}

