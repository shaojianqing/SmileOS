#include "../const/const.h"
#include "../type/type.h"
#include "../gui/resource.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/graphPanel.h"
#include "dataSetting.h"
#include "dataGraph.h"

Button *barGraphBtn;

Button *lineGraphBtn;

Button *hybridGraphBtn;

Button *financeGraphBtn;

GraphPanel *graphPanel;

Factory dataGraphFactory;

extern Process *dataGraphProcess;

void onBarGraphBtnClick(Button *this, MouseEvent *event);

void onLineGraphBtnClick(Button *this, MouseEvent *event);

void onHybridGraphBtnClick(Button *this, MouseEvent *event);

void onFinanceGraphBtnClick(Button *this, MouseEvent *event);

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
		(*dataGraphProcess).tss.esp = allocPage(64 * 1024) + 64 * 1024;
		(*dataGraphProcess).tss.eip = (int) &dataGraphApplicationMain;
		(*dataGraphProcess).tss.es = 2 * 8;
		(*dataGraphProcess).tss.cs = 1 * 8;
		(*dataGraphProcess).tss.ss = 2 * 8;
		(*dataGraphProcess).tss.ds = 2 * 8;
		(*dataGraphProcess).tss.fs = 2 * 8;
		(*dataGraphProcess).tss.gs = 2 * 8;
		(*dataGraphProcess).tss.cr3 = 0x60000;

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
        (*sheet).buffer = (char *)allocPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);
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

		Color shadowColor;
        shadowColor.red = 0x55;
        shadowColor.green = 0x55;
        shadowColor.blue = 0x55;

       	drawCornerRect(mainView, 0, 0, (*mainView).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect(mainView, 1, 1, (*mainView).width-2, 20, startColor, endColor, corner, DIRECTION_UP);
        drawRect(mainView, 0, 21, (*mainView).width, 540, mainBgColor);
		drawRect(mainView, 1, 21, (*mainView).width-2, 538, mainColor);

		printString(mainView, "DataGraph", 9, 350, 4, textColor, shadowColor);

		graphPanel = createGraphPanel(5, 60, 790, 494);
		(*mainView).addSubView(mainView, (View *)graphPanel);
		(*mainView).addSubView(mainView, (*graphPanel).canvas);

		Image *image = (Image *)loadImageFromStorage(ico_btn_bar_graph);
		barGraphBtn = createButton(5, 24, 140, 32, &dataGraphFactory, image);
		(*barGraphBtn).initButton(barGraphBtn, "Bar Graph", 9, ButtonStyleLightGray);
		(*barGraphBtn).onMouseClick = onBarGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)barGraphBtn);

		lineGraphBtn = createButton(150, 24, 140, 32, &dataGraphFactory, null);
		(*lineGraphBtn).initButton(lineGraphBtn, "Line Graph", 10, ButtonStyleLightGray);
		(*lineGraphBtn).onMouseClick = onLineGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)lineGraphBtn);

		hybridGraphBtn = createButton(295, 24, 140, 32, &dataGraphFactory, null);
		(*hybridGraphBtn).initButton(hybridGraphBtn, "Hybrid Graph", 12, ButtonStyleLightGray);
		(*hybridGraphBtn).onMouseClick = onHybridGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)hybridGraphBtn);

		financeGraphBtn = createButton(440, 24, 140, 32, &dataGraphFactory, null);
		(*financeGraphBtn).initButton(financeGraphBtn, "Stack Graph", 11, ButtonStyleLightGray);
		(*financeGraphBtn).onMouseClick = onFinanceGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)financeGraphBtn);

		loadContentView(sheet, mainView);	
    }
}

void onBarGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawBarGraph;
	(*graphPanel).drawGraph(graphPanel);
}

void onLineGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawLineGraph;
	(*graphPanel).drawGraph(graphPanel);
}

void onHybridGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawBarGraph;
	(*graphPanel).drawGraph(graphPanel);
	(*graphPanel).drawGraph = drawLineGraph;
	(*graphPanel).drawGraph(graphPanel);
}

void onFinanceGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawLineGraph;
	(*graphPanel).drawGraph(graphPanel);
}

