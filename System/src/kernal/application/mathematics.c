#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../gui/graphics.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/event/buttonEvent.h"
#include "../gui/factory/factory.h"
#include "../gui/view/button.h"
#include "../gui/view/coorPanel.h"
#include "../system/descriptor.h"
#include "../execute/execute.h"
#include "../process/process.h"

extern Process *mathematicsProcess;

static Button *linearBtn;

static Button *quadraticBtn;

static Button *circleBtn;

static Button *ellipseBtn;

static CoorPanel *coorPanel;

static Factory mathematicsFactory;

static void drawCoorPoint(View *view, int x, int y, Color color);

static void onLinearBtnClick(Button *this, MouseEvent *event);

static void onQuadraticBtnClick(Button *this, MouseEvent *event);

static void onCircleBtnClick(Button *this, MouseEvent *event);

static void onEllipseBtnClick(Button *this, MouseEvent *event);

static void drawCircleFunction(CoorPanel *coorPanel);

static void drawLinearFunction(CoorPanel *coorPanel);

static void drawQuadraticFunction(CoorPanel *coorPanel);

static void drawEillpseFunction(CoorPanel *coorPanel);

static void mathematicsApplicationMain();

static void prepareWindowSheetMath(Sheet *sheet);

static void mathematicsOnTimer()
{
	mathematicsFactory.changeButtonStatus(&mathematicsFactory);
}

void startMathematicsApplication()
{
	if (mathematicsProcess==null) {
		mathematicsProcess = requestProcess();
		(*mathematicsProcess).tss.esp = allocPage(64 * 1024) + 64 * 1024;
		(*mathematicsProcess).tss.eip = (int) &mathematicsApplicationMain;
		(*mathematicsProcess).tss.es = 2 * 8;
		(*mathematicsProcess).tss.cs = 1 * 8;
		(*mathematicsProcess).tss.ss = 2 * 8;
		(*mathematicsProcess).tss.ds = 2 * 8;
		(*mathematicsProcess).tss.fs = 2 * 8;
		(*mathematicsProcess).tss.gs = 2 * 8;
		(*mathematicsProcess).tss.cr3 = 0x60000;

		startRunProcess(mathematicsProcess, 4);
	}
}

static void mathematicsApplicationMain()
{
	initFactory(&mathematicsFactory, mathematicsOnTimer);
	
	Sheet *winMathematics = prepareSheet();
    prepareWindowSheetMath(winMathematics);
    loadWindowSheet(winMathematics);
	(*mathematicsProcess).mainWindow = winMathematics;

	while(TRUE) {
		mathematicsFactory.deselectButton(&mathematicsFactory);
		mathematicsFactory.doProcessEvent(&mathematicsFactory);
	}
}

static void prepareWindowSheetMath(Sheet *sheet)
{
    if (sheet != null) {
        (*sheet).x = 80;
        (*sheet).y = 80;
        (*sheet).width = 800;
        (*sheet).height = 560;
        (*sheet).buffer = (char *)allocPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);
		View *mainView = createView(0, 0, 800, 560);

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

		printString(mainView, "Mathematics", 12, 350, 4, textColor, shadowColor);

		coorPanel = createCoorPanel(5, 60, 790, 494);
		(*mainView).addSubView(mainView, (View *)coorPanel);
		(*mainView).addSubView(mainView, (*coorPanel).canvas);

		linearBtn = createButton(5, 24, 120, 32, &mathematicsFactory, null);
		(*linearBtn).initButton(linearBtn, "Linear", 6, ButtonStyleLightGray);
		(*linearBtn).onMouseClick = onLinearBtnClick;
		(*mainView).addSubView(mainView, (View *)linearBtn);

		quadraticBtn = createButton(130, 24, 120, 32, &mathematicsFactory, null);
		(*quadraticBtn).initButton(quadraticBtn, "Quadratic", 9, ButtonStyleLightGray);
		(*quadraticBtn).onMouseClick = onQuadraticBtnClick;
		(*mainView).addSubView(mainView, (View *)quadraticBtn);

		circleBtn = createButton(255, 24, 120, 32, &mathematicsFactory, null);
		(*circleBtn).initButton(circleBtn, "Circle", 6, ButtonStyleLightGray);
		(*circleBtn).onMouseClick = onCircleBtnClick;
		(*mainView).addSubView(mainView, (View *)circleBtn);

		ellipseBtn = createButton(380, 24, 120, 32, &mathematicsFactory, null);
		(*ellipseBtn).initButton(ellipseBtn, "Ellipse", 7, ButtonStyleLightGray);
		(*ellipseBtn).onMouseClick = onEllipseBtnClick;
		(*mainView).addSubView(mainView, (View *)ellipseBtn);

		loadContentView(sheet, mainView);	
    }
}

static void drawCoorPoint(View *view, int x, int y, Color color)
{
	int xb = ORIGIN_X+x;
	int yb = ORIGIN_Y-y;

	int width=(*view).width;
	int height=(*view).height;

	if (xb<width && yb<height && xb>0 && yb>0) {
		drawBoldPoint(view, xb, yb, color);
	}
}

static void drawLinearFunction(CoorPanel *coorPanel)
{
	if (coorPanel!=null && (*coorPanel).canvas!=null) {		
		View *canvas = (*coorPanel).canvas;
		(*canvas).clearView(canvas);
		
		Color linearColor;
        linearColor.red = 120;
        linearColor.green = 180;
        linearColor.blue = 250;

		Color shadowColor;
        shadowColor.red = 120;
        shadowColor.green = 180;
        shadowColor.blue = 250;

		int x=0, y=0;		
		for (x=-400;x<=400;++x) {
			y=x-80;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=x-80", 6, 560, 160, linearColor, shadowColor);

		linearColor.red = 150;
        linearColor.green = 10;
        linearColor.blue = 150;
		
		for (x=-400;x<=400;++x) {
			y=x;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=x", 3, 470, 160, linearColor, shadowColor);

        linearColor.red = 180;
        linearColor.green = 160;
        linearColor.blue = 80;
	
		for (x=-400;x<=400;++x) {
			y=100;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=100", 6, 200, 160, linearColor, shadowColor);

		linearColor.red = 240;
        linearColor.green = 100;
        linearColor.blue = 20;
	
		for (y=-300;y<=300;++y) {
			x=-100;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "x=-100", 6, 300, 440, linearColor, shadowColor);

		linearColor.red = 60;
        linearColor.green = 200;
        linearColor.blue = 20;
	
		for (x=-400;x<=400;++x) {
			y=80-x;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=80-x", 6, 550, 300, linearColor, shadowColor);

		linearColor.red = 255;
        linearColor.green = 10;
        linearColor.blue = 220;
	
		for (x=-400;x<=400;++x) {
			y=-x;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=-x", 4, 470, 300, linearColor, shadowColor);

		View *view = (View *)coorPanel;
		(*view).refreshRectView(view);
		(*canvas).refreshRectView(canvas);
	}
}

static void drawQuadraticFunction(CoorPanel *coorPanel)
{
	if (coorPanel!=null && (*coorPanel).canvas!=null) {		
		View *canvas = (*coorPanel).canvas;
		(*canvas).clearView(canvas);
		
		Color linearColor;
        linearColor.red = 120;
        linearColor.green = 180;
        linearColor.blue = 250;

		Color shadowColor;
        shadowColor.red = 120;
        shadowColor.green = 180;
        shadowColor.blue = 250;

		int x=0, y=0;		
		for (x=-400;x<=400;++x) {
			y=x*x/200+x-100;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=x*x/200+x-100", 15, 60, 100, linearColor, shadowColor);

		linearColor.red = 20;
        linearColor.green = 180;
        linearColor.blue = 180;
		
		for (x=-400;x<=400;++x) {
			y=x*x/200-x-100;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=x*x/200-x-100", 15, 570, 360, linearColor, shadowColor);

		linearColor.red = 250;
        linearColor.green = 120;
        linearColor.blue = 100;
		
		for (x=-400;x<=400;++x) {
			y=100-x*x/200+x;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=100-x*x/200+x", 15, 570, 100, linearColor, shadowColor);
		
		linearColor.red = 255;
        linearColor.green = 20;
        linearColor.blue = 220;
		
		for (x=-400;x<=400;++x) {
			y=100-x*x/200-x;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "y=100-x*x/200-x", 15, 60, 380, linearColor, shadowColor);
		
		linearColor.red = 255;
        linearColor.green = 80;
        linearColor.blue = 0;
	
		for (y=-400;y<=400;++y) {
			x=-100;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "x=-100", 6, 300, 300, linearColor, shadowColor);

		linearColor.red = 150;
        linearColor.green = 0;
        linearColor.blue = 150;
	
		for (y=-400;y<=400;++y) {
			x=100;
			drawCoorPoint(canvas, x, y, linearColor);	
		}
		printString(canvas, "x=100", 5, 500, 300, linearColor, shadowColor);

		View *view = (View *)coorPanel;
		(*view).refreshRectView(view);
		(*canvas).refreshRectView(canvas);
	}
}

static void drawCircleFunction(CoorPanel *coorPanel)
{
	if (coorPanel!=null && (*coorPanel).canvas!=null) {		
		View *canvas = (*coorPanel).canvas;
		(*canvas).clearView(canvas);
		
		Color linearColor;
        linearColor.red = 255;
        linearColor.green = 10;
        linearColor.blue = 200;

		Color shadowColor;
        shadowColor.red = 255;
        shadowColor.green = 10;
        shadowColor.blue = 200;

		int x=0, y=0;		
		for (x=-160;x<=160;++x) {
			for (y=-160;y<=160;++y) {
				if ((x*x+y*y<160*160) && (x*x+y*y>158*158)) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}
		printString(canvas, "x^2+y^2=160^160", 15, 540, 160, linearColor, shadowColor);

		linearColor.red = 20;
        linearColor.green = 220;
        linearColor.blue = 180;
	
		for (x=0;x<=160;++x) {
			for (y=0;y<=160;++y) {
				if (((x-80)*(x-80)+(y-80)*(y-80)<80*80) && ((x-80)*(x-80)+(y-80)*(y-80)>78*78)) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}
		printString(canvas, "x^2+y^2=160^160", 15, 540, 200, linearColor, shadowColor);

		linearColor.red = 20;
        linearColor.green = 220;
        linearColor.blue = 180;
	
		for (x=-160;x<=0;++x) {
			for (y=0;y<=160;++y) {
				if (((x+80)*(x+80)+(y-80)*(y-80)<80*80) && ((x+80)*(x+80)+(y-80)*(y-80)>78*78)) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}
		printString(canvas, "x^2+y^2=160^160", 15, 540, 200, linearColor, shadowColor);

		linearColor.red = 20;
        linearColor.green = 220;
        linearColor.blue = 180;
	
		for (x=0;x<=160;++x) {
			for (y=-160;y<=0;++y) {
				if (((x-80)*(x-80)+(y+80)*(y+80)<80*80) && ((x-80)*(x-80)+(y+80)*(y+80)>78*78)) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}
		printString(canvas, "x^2+y^2=160^160", 15, 540, 200, linearColor, shadowColor);

		linearColor.red = 20;
        linearColor.green = 220;
        linearColor.blue = 180;
	
		for (x=-160;x<=0;++x) {
			for (y=-160;y<=0;++y) {
				if (((x+80)*(x+80)+(y+80)*(y+80)<80*80) && ((x+80)*(x+80)+(y+80)*(y+80)>78*78)) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}
		printString(canvas, "x^2+y^2=160^160", 15, 540, 200, linearColor, shadowColor);

		linearColor.red = 20;
        linearColor.green = 80;
        linearColor.blue = 220;
	
		for (x=-80;x<=80;++x) {
			for (y=-80;y<=80;++y) {
				if ((x*x+y*y<80*80) && (x*x+y*y>78*78)) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}
		printString(canvas, "x^2+y^2=160^160", 15, 540, 200, linearColor, shadowColor);

		View *view = (View *)coorPanel;
		(*view).refreshRectView(view);
		(*canvas).refreshRectView(canvas);
	}
}

static void drawEillpseFunction(CoorPanel *coorPanel)
{
	if (coorPanel!=null && (*coorPanel).canvas!=null) {		
		View *canvas = (*coorPanel).canvas;
		(*canvas).clearView(canvas);
		
		Color linearColor;
        linearColor.red = 255;
        linearColor.green = 10;
        linearColor.blue = 200;

		int x=0, y=0;		
		for (x=-300;x<=300;++x) {
			for (y=-300;y<=300;++y) {
				if (x*x+y*y*4<40000 && x*x+y*y*4>39204) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}

		linearColor.red = 20;
        linearColor.green = 220;
        linearColor.blue = 180;
	
		for (x=-100;x<=100;++x) {
			for (y=-100;y<=100;++y) {
				if (x*x+y*y<10000 && x*x+y*y>98*98) {
					drawCoorPoint(canvas, x, y, linearColor);
				}				
			}			
		}

		View *view = (View *)coorPanel;
		(*view).refreshRectView(view);
		(*canvas).refreshRectView(canvas);
	}
}

static void onLinearBtnClick(Button *this, MouseEvent *event)
{
	(*coorPanel).drawFuncation = drawLinearFunction;
	(*coorPanel).drawFuncation(coorPanel);
}

static void onQuadraticBtnClick(Button *this, MouseEvent *event)
{
	(*coorPanel).drawFuncation = drawQuadraticFunction;
	(*coorPanel).drawFuncation(coorPanel);
}

static void onCircleBtnClick(Button *this, MouseEvent *event)
{
	(*coorPanel).drawFuncation = drawCircleFunction;
	(*coorPanel).drawFuncation(coorPanel);
}

static void onEllipseBtnClick(Button *this, MouseEvent *event)
{
	(*coorPanel).drawFuncation = drawEillpseFunction;
	(*coorPanel).drawFuncation(coorPanel);
}

