#include "../const/const.h"
#include "../type/type.h"
#include "../gui/resource.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/item/headerItem.h"
#include "../gui/view/item/gridDataItem.h"
#include "../gui/view/gridPanel.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "data/processData.h"
#include "systemInfo.h"

extern Process *sysInfoProcess;

static Factory sysInfoFactory;

static Button *processInfoBtn;

static Button *memoryInfoBtn;

static HeaderItem headerItemList[5];

static ProcessData processDataList[5];

static GridPanel *processDataGrid;

static void prepareProcessHeaderList();

static void prepareProcessDataList();

static void sysInfoApplicationMain();

static void prepareWindowSheetSys(Sheet *sheet);

static GridDataItem *processItemRender(GridPanel *this, u32 index, int width, int height);

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
	}
}

static void sysInfoApplicationMain()
{
	initFactory(&sysInfoFactory, sysInfoOnTimer);
	
	Sheet *winSysInfo = prepareSheet();
    prepareWindowSheetSys(winSysInfo);
    loadWindowSheet(winSysInfo);
	(*sysInfoProcess).mainWindow = winSysInfo;

	while(TRUE) {
		sysInfoFactory.deselectButton(&sysInfoFactory);
		sysInfoFactory.doProcessEvent(&sysInfoFactory);
	}
}

static void prepareWindowSheetSys(Sheet *sheet)
{
    if (sheet != null) {
        (*sheet).x = 460;
        (*sheet).y = 50;
        (*sheet).width = 500;
        (*sheet).height = 560;
        (*sheet).buffer = (u8 *)allocPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 500, 560);

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

        drawCornerRect(mainView, 0, 0, (*mainView).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 20, startColor, endColor, corner, DIRECTION_UP);
        drawRect(mainView, 0, 21, (*mainView).width, 540, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 538, mainColor);

		printString(mainView, "System Infomation", 18, 120, 4, textColor, shadowColor);

		Image *processIco = (Image *)loadImageFromStorage(ico_btn_sys_process);
		processInfoBtn = createButton(5, 24, 150, 32, &sysInfoFactory, processIco);
		(*processInfoBtn).initButton(processInfoBtn, "Process Info", 12, ButtonStyleLightGray);
		(*processInfoBtn).onMouseClick = onProcessBtnClick;
		(*mainView).addSubView(mainView, (View *)processInfoBtn);

		memoryInfoBtn = createButton(160, 24, 150, 32, &sysInfoFactory, null);
		(*memoryInfoBtn).initButton(memoryInfoBtn, "Memory Info", 11, ButtonStyleLightGray);
		(*memoryInfoBtn).onMouseClick = onMemoryBtnClick;
		(*mainView).addSubView(mainView, (View *)memoryInfoBtn);

		prepareProcessHeaderList();
		prepareProcessDataList();

		processDataGrid = createGridPanel(5, 60, 490, 495);
		(*processDataGrid).initPanel(processDataGrid, headerItemList, 5);
		(*processDataGrid).renderDataGrid(processDataGrid, 5, processItemRender);
		(*mainView).addSubView(mainView, (View *)processDataGrid);

		loadContentView(sheet, mainView);
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
	(*processData).pId = 22;

	processData = processDataList+1;
	(*processData).name = "Calculator";
	(*processData).wordCount = 10;
	(*processData).pId = 21;

	processData = processDataList+2;
	(*processData).name = "Mathmatics";
	(*processData).wordCount = 10;
	(*processData).pId = 18;

	processData = processDataList+3;
	(*processData).name = "DataGraph";
	(*processData).wordCount = 9;
	(*processData).pId = 88;

	processData = processDataList+4;
	(*processData).name = "System Info";
	(*processData).wordCount = 11;
	(*processData).pId = 32;
}

static void onProcessBtnClick(Button *this, MouseEvent *event)
{
	
}

static void onMemoryBtnClick(Button *this, MouseEvent *event)
{
	
}

