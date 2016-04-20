#include "../../const/const.h"
#include "../../type/type.h"
#include "../sheet.h"
#include "../color.h"
#include "../corner.h"
#include "view.h"
#include "../graphics.h"
#include "coorPanel.h"

static void drawBackground(CoorPanel *this, int width, int height);

static void drawGridView(CoorPanel *this, int width, int height);

static void drawCoorindate(CoorPanel *this, int width, int height);

static void drawBorder(CoorPanel *this, int width, int height);

static void onMouseDown(View *this, MouseEvent *event);

static void initCoorPanel(CoorPanel *this);

CoorPanel *createCoorPanel(int x, int y, int w, int h)
{
	CoorPanel *coorPanel = (CoorPanel *)allocPage(sizeof(CoorPanel));
	coorPanel = (CoorPanel *)initWithViewFunction((View*)coorPanel, x, y, w, h);
	(*coorPanel).canvas = createView(x, y, w, h);	
	(*coorPanel).initPanel = initCoorPanel;
	(*coorPanel).initPanel(coorPanel);	
	(*coorPanel).view.onMouseDown = onMouseDown;
	
	return coorPanel;
}

static void initCoorPanel(CoorPanel *this)
{
	if (this!=null) {		
		int width = (*this).view.width;
		int height = (*this).view.height;
		
		drawBackground(this, width, height);		
		drawGridView(this, width, height);
		drawCoorindate(this, width, height);
		drawBorder(this, width, height);
	}
}

static void drawBackground(CoorPanel *this, int width, int height)
{
	Color color;
    color.red = 40;
    color.green = 60;
    color.blue = 80;
	
	drawRect((View *)this, 0, 0, width, height, color);
}

static void drawGridView(CoorPanel *this, int width, int height)
{
	Color color;
    color.red = 90;
    color.green = 90;
    color.blue = 80;

	int i=0;
	for (i=1;i<=48;++i) {
		drawLine((View *)this, 0, i*10, width, i*10, color, LINE_THIN);	
	}
	
	for (i=1;i<=78;++i) {
		drawLine((View *)this, i*10, 0, i*10, height-1, color, LINE_THIN);	
	}
}

static void drawCoorindate(CoorPanel *this, int width, int height)
{
	Color color;
    color.red = 160;
    color.green = 180;
    color.blue = 80;

	int i=0;
	for (i=1;i<=48;++i) {
		drawLine((View *)this, 390, i*10, 394, i*10, color, LINE_THIN);	
	}
	
	for (i=1;i<=78;++i) {
		drawLine((View *)this, i*10, 236, i*10, 240, color, LINE_THIN);	
	}
	
	drawLine((View *)this, 10, 240, width-10, 240, color, LINE_BOLD);
	drawLine((View *)this, 390, 10, 390, height-10, color, LINE_BOLD);
}

static void drawBorder(CoorPanel *this, int width, int height)
{
	Color color;
	color.red = 80;
    color.green = 100;
    color.blue = 120;
	
	drawLine((View *)this, 0, 0, width, 0, color, LINE_THIN);
	drawLine((View *)this, 0, 0, 0, height, color, LINE_THIN);
	drawLine((View *)this, 0, height-1, width, height-1, color, LINE_THIN);
	drawLine((View *)this, width-1, 0, width-1, height, color, LINE_THIN);
}

static void drawFirstLine(CoorPanel *this)
{
	Color color;
	color.red = 160;
    color.green = 160;
    color.blue = 240;

	Color shadowColor;
	shadowColor.red = 160;
    shadowColor.green = 160;
    shadowColor.blue = 240;
	
	drawLine((*this).canvas, 10, 10, 300, 400, color, LINE_BOLD);

	drawLine((*this).canvas, 10, 10, 700, 200, color, LINE_BOLD);

	printString((*this).canvas, "y=2*x-8", 7, 600, 160, color, shadowColor);

	View *canvas = (*this).canvas;
	(*canvas).refreshRectView(canvas);
}

static void onMouseDown(View *this, MouseEvent *event)
{}
