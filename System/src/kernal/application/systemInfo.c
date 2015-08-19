#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../process/process.h"
#include "systemInfo.h"

extern Process *sysInfoProcess;

void sysInfoApplicationMain();

void prepareWindowSheetSys(Sheet *sheet);

void startSysInfoApplication()
{
	if (sysInfoProcess==null) {
		sysInfoProcess = requestProcess();
		(*sysInfoProcess).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
		(*sysInfoProcess).tss.eip = (int) &sysInfoApplicationMain;
		(*sysInfoProcess).tss.es = 2 * 8;
		(*sysInfoProcess).tss.cs = 1 * 8;
		(*sysInfoProcess).tss.ss = 2 * 8;
		(*sysInfoProcess).tss.ds = 2 * 8;
		(*sysInfoProcess).tss.fs = 2 * 8;
		(*sysInfoProcess).tss.gs = 2 * 8;
		startRunProcess(sysInfoProcess, 4);
	}
}

void sysInfoApplicationMain()
{
	Sheet *winSysInfo = prepareSheet();
    prepareWindowSheetSys(winSysInfo);
    loadWindowSheet(winSysInfo);
	(*sysInfoProcess).mainWindow = winSysInfo;
	int count = 0;

	while(TRUE) {
		count++;
	}
}

void prepareWindowSheetSys(Sheet *sheet)
{
    if (sheet != null) {
        (*sheet).x = 140;
        (*sheet).y = 80;
        (*sheet).width = 800;
        (*sheet).height = 560;
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
        mainColor.red = 200;
        mainColor.green = 200;
        mainColor.blue = 180;

		Color textColor;
        textColor.red = 0x55;
        textColor.green = 0x55;
        textColor.blue = 0x55;

        drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-2, 20, startColor, endColor, corner);
        //drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 539, mainBgColor);
        //drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-2, 538, mainColor);

		printString(sheet, "System", 8, 370, 4, textColor);
    }
}


