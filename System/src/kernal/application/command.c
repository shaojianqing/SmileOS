#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "command.h"

extern Process *commandProcess;

void commandApplicationMain();

void prepareWindowSheetCmd(Sheet *sheet);

void startCommandApplication()
{
	if (commandProcess==null) {
		commandProcess = requestProcess();
		(*commandProcess).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
		(*commandProcess).tss.eip = (int) &commandApplicationMain;
		(*commandProcess).tss.es = 2 * 8;
		(*commandProcess).tss.cs = 1 * 8;
		(*commandProcess).tss.ss = 2 * 8;
		(*commandProcess).tss.ds = 2 * 8;
		(*commandProcess).tss.fs = 2 * 8;
		(*commandProcess).tss.gs = 2 * 8;
		(*commandProcess).tss.cr3 = 0x60000;

		startRunProcess(commandProcess, 4);
	}
}

void commandApplicationMain()
{
	Sheet *winCommand = prepareSheet();
    prepareWindowSheetCmd(winCommand);
    loadWindowSheet(winCommand);
	(*commandProcess).mainWindow = winCommand;
	int count = 0;

	while(TRUE) {
		count++;
	}
}

void prepareWindowSheetCmd(Sheet *sheet)
{
    if (sheet != null) {
        (*sheet).x = 80;
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
        mainColor.red = 20;
        mainColor.green = 40;
        mainColor.blue = 60;

		Color textColor;
        textColor.red = 0x55;
        textColor.green = 0x55;
        textColor.blue = 0x55;

        drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-2, 20, startColor, endColor, corner);
        //drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 539, mainBgColor);
        //drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-2, 538, mainColor);

		printString(sheet, "Command", 8, 370, 4, textColor);
    }
}


