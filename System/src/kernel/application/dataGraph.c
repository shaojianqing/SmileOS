#include "../const/const.h"
#include "../type/type.h"
#include "../gui/resource.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../gui/image.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "../gui/view/view.h"
#include "../gui/view/event.h"
#include "../gui/graphics.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/imageButton.h"
#include "../gui/view/graphPanel.h"
#include "dataSetting.h"
#include "dataGraph.h"

extern Process *dataGraphProcess;

static Sheet *winDataGraph;

static Button *barGraphBtn;

static Button *lineGraphBtn;

static Button *hybridGraphBtn;

static Button *financeGraphBtn;

static ImageButton *closeBtn;

static ImageButton *minizBtn;

static GraphPanel *graphPanel;

static Factory dataGraphFactory;

static void onCloseBtnClick(ImageButton *this, MouseEvent *event);

static void onMinizBtnClick(ImageButton *this, MouseEvent *event);

static void onBarGraphBtnClick(Button *this, MouseEvent *event);

static void onLineGraphBtnClick(Button *this, MouseEvent *event);

static void onHybridGraphBtnClick(Button *this, MouseEvent *event);

static void onFinanceGraphBtnClick(Button *this, MouseEvent *event);

static void dataGraphApplicationMain();

static void prepareWindowSheetGraph();

static void dataGraphOnTimer()
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
	} else {
		if (winDataGraph!=null && (*winDataGraph).visible==FALSE) {
			showWindowSheet(winDataGraph);
		}	
	}
}

static void dataGraphApplicationMain()
{
	initFactory(&dataGraphFactory, dataGraphOnTimer);
	
	winDataGraph = prepareSheet();
    prepareWindowSheetGraph(winDataGraph);
    loadWindowSheet(winDataGraph);
	(*dataGraphProcess).mainWindow = winDataGraph;

	while(TRUE) {
		dataGraphFactory.deselectButton(&dataGraphFactory);
		dataGraphFactory.doProcessEvent(&dataGraphFactory);
	}
}

static void prepareWindowSheetGraph()
{
    if (winDataGraph != null) {
        (*winDataGraph).x = 60;
        (*winDataGraph).y = 60;
        (*winDataGraph).width = 800;
        (*winDataGraph).height = 560;
        (*winDataGraph).buffer = (u8 *)allocPage((*winDataGraph).width*(*winDataGraph).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 800, 560);

        resetSheet(winDataGraph);

        Color startColor;
		startColor.red = 20;
		startColor.green = 36;
		startColor.blue = 54;

		Color endColor;
		endColor.red = 32;
		endColor.green = 42;
		endColor.blue = 60;

		Corner corner;
		corner.leftTop = 2;
		corner.rightTop = 2;
		corner.leftBtm = 0;
		corner.rightBtm = 0;

		Color mainBgColor;
		mainBgColor.red = 120;
		mainBgColor.green = 120;
		mainBgColor.blue = 120;

		Color mainColor;
		mainColor.red = 20;
		mainColor.green = 36;
		mainColor.blue = 54;

		Color textColor;
		textColor.red = 0xaa;
		textColor.green = 0xbb;
		textColor.blue = 0x66;

		Color shadowColor;
		shadowColor.red = 0xaa;
		shadowColor.green = 0xbb;
		shadowColor.blue = 0x66;

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

		printString(mainView, "DataGraph", 9, 350, 4, textColor, shadowColor);

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

		graphPanel = createGraphPanel(5, 60, 790, 494);
		(*mainView).addSubView(mainView, (View *)graphPanel);
		(*mainView).addSubView(mainView, (*graphPanel).canvas);

		Image *barIco = (Image *)loadImageFromStorage(ico_btn_bar_graph);
		barGraphBtn = createButton(5, 24, 140, 32, &dataGraphFactory, barIco);
		(*barGraphBtn).initButton(barGraphBtn, "Bar Graph", 9, ButtonStyleBlackBlue);
		(*barGraphBtn).onMouseClick = onBarGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)barGraphBtn);
		(*barIco).release(barIco);

		Image *lineIco = (Image *)loadImageFromStorage(ico_btn_line_graph);
		lineGraphBtn = createButton(150, 24, 140, 32, &dataGraphFactory, lineIco);
		(*lineGraphBtn).initButton(lineGraphBtn, "Line Graph", 10, ButtonStyleBlackBlue);
		(*lineGraphBtn).onMouseClick = onLineGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)lineGraphBtn);
		(*lineIco).release(lineIco);

		Image *hybdIco = (Image *)loadImageFromStorage(ico_btn_hybd_graph);
		hybridGraphBtn = createButton(295, 24, 140, 32, &dataGraphFactory, hybdIco);
		(*hybridGraphBtn).initButton(hybridGraphBtn, "Hybrid Graph", 12, ButtonStyleBlackBlue);
		(*hybridGraphBtn).onMouseClick = onHybridGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)hybridGraphBtn);
		(*hybdIco).release(hybdIco);

		Image *finIco = (Image *)loadImageFromStorage(ico_btn_fin_graph);
		financeGraphBtn = createButton(440, 24, 140, 32, &dataGraphFactory, finIco);
		(*financeGraphBtn).initButton(financeGraphBtn, "Stack Graph", 11, ButtonStyleBlackBlue);
		(*financeGraphBtn).onMouseClick = onFinanceGraphBtnClick;
		(*mainView).addSubView(mainView, (View *)financeGraphBtn);
		(*finIco).release(finIco);

		loadContentView(winDataGraph, mainView);	
    }
}

static void onBarGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawBarGraph;
	(*graphPanel).drawGraph(graphPanel);
}

static void onLineGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawLineGraph;
	(*graphPanel).drawGraph(graphPanel);
}

static void onHybridGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawBarGraph;
	(*graphPanel).drawGraph(graphPanel);
	(*graphPanel).drawGraph = drawLineGraph;
	(*graphPanel).drawGraph(graphPanel);
}

static void onFinanceGraphBtnClick(Button *this, MouseEvent *event)
{
	(*graphPanel).drawGraph = drawLineGraph;
	(*graphPanel).drawGraph(graphPanel);
}

static void onCloseBtnClick(ImageButton *this, MouseEvent *event)
{
	
}

static void onMinizBtnClick(ImageButton *this, MouseEvent *event)
{
	hideWindowSheet(winDataGraph);
}

