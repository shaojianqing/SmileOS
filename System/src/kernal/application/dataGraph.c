#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../process/process.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/graphPanel.h"
#include "dataGraph.h"

Button *barGraphBtn;

Button *lineGraphBtn;

GraphPanel *graphPanel;

Factory dataGraphFactory;

extern Process *dataGraphProcess;

void onBarGraphBtnClick(Button *this, MouseEvent *event);

void onLineGraphBtnClick(Button *this, MouseEvent *event);

void drawBarGraph(GraphPanel *this);

void dataGraphApplicationMain();

void prepareWindowSheetGraph(Sheet *sheet);

void dataGraphOnTimer()
{
	dataGraphFactory.changeButtonStatus(&dataGraphFactory);
}

void startDataGraphApplication()
{
	if (dataGraphProcess==null) {
		dataGraphProcess = requestProcess();
		(*dataGraphProcess).tss.esp = allocMemory(64 * 1024) + 64 * 1024;
		(*dataGraphProcess).tss.eip = (int) &dataGraphApplicationMain;
		(*dataGraphProcess).tss.es = 2 * 8;
		(*dataGraphProcess).tss.cs = 1 * 8;
		(*dataGraphProcess).tss.ss = 2 * 8;
		(*dataGraphProcess).tss.ds = 2 * 8;
		(*dataGraphProcess).tss.fs = 2 * 8;
		(*dataGraphProcess).tss.gs = 2 * 8;
		startRunProcess(dataGraphProcess, 4);
	}
}

void dataGraphApplicationMain()
{
	initFactory(&dataGraphFactory, dataGraphOnTimer);
	
	Sheet *winDataGraph = prepareSheet();
    prepareWindowSheetGraph(winDataGraph);
    loadWindowSheet(winDataGraph);
	(*dataGraphProcess).mainWindow = winDataGraph;

	while(TRUE) {
		dataGraphFactory.deselectButton(&dataGraphFactory);
		dataGraphFactory.doProcessEvent(&dataGraphFactory);
	}
}

void prepareWindowSheetGraph(Sheet *sheet)
{
    if (sheet != null) {
        (*sheet).x = 60;
        (*sheet).y = 60;
        (*sheet).width = 800;
        (*sheet).height = 560;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 800, 560);

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

		printString(mainView, "DataGraph", 9, 350, 4, textColor);

		graphPanel = createGraphPanel(5, 60, 790, 494);
		(*mainView).addSubView(mainView, (View *)graphPanel);
		(*mainView).addSubView(mainView, (*graphPanel).canvas);

		barGraphBtn = createButton(5, 24, 120, 32, &dataGraphFactory);
		(*barGraphBtn).initButton(barGraphBtn, "Bar Graph", 9, ButtonStyleLightGray);
		(*barGraphBtn).onMouseClick = onBarGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)barGraphBtn);

		lineGraphBtn = createButton(130, 24, 120, 32, &dataGraphFactory);
		(*lineGraphBtn).initButton(lineGraphBtn, "Line Graph", 10, ButtonStyleLightGray);
		(*lineGraphBtn).onMouseClick = onLineGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)lineGraphBtn);

		loadContentView(sheet, mainView);	
    }
}

void drawBarGraph(GraphPanel *this)
{
	if (this!=null && (*this).canvas!=null) {
		View *canvas = (*this).canvas;
		(*canvas).clearView(canvas);
		
		Color startColor;
		startColor.red = 60;
    	startColor.green = 140;
    	startColor.blue = 210;

		Color endColor;
		endColor.red = 100;
    	endColor.green = 180;
    	endColor.blue = 250;

		Corner corner;
		corner.leftTop = 2;
		corner.rightTop = 2;
		corner.leftBtm = 2;
		corner.rightBtm = 2;

		drawGradualHorizontalCornerRect(canvas, 100, 100, 40, 360, startColor, endColor, corner, DIRECTION_UP);

		View *view = (View *)graphPanel;
		(*view).refreshRectView(view);
		(*canvas).refreshRectView(canvas);
	}
}

void onBarGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawBarGraph;
	(*graphPanel).drawGraph(graphPanel);
}

void onLineGraphBtnClick(Button *this, MouseEvent *event)
{
	showIntegerValue(3663, 100, 50);
}


