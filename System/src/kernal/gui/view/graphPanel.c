#include "../../const/const.h"
#include "../../type/type.h"
#include "view.h"
#include "../sheet.h"
#include "../color.h"
#include "../corner.h"
#include "../graphics.h"
#include "graphPanel.h"

static void drawBackground(GraphPanel *this, int width, int height);

static void drawGridView(GraphPanel *this, int width, int height);

static void drawCoorindate(GraphPanel *this, int width, int height);

static void drawBorder(GraphPanel *this, int width, int height);

static void onMouseDown(View *this, MouseEvent *event);

GraphPanel *createGraphPanel(int x, int y, int w, int h)
{
	GraphPanel *graphPanel = (GraphPanel *)alloc(sizeof(GraphPanel));
	graphPanel = (GraphPanel*)initWithViewFunction((View*)graphPanel, x, y, w, h);
	(*graphPanel).canvas = createView(x, y, w, h);	
	(*graphPanel).initPanel = initGraphPanel;
	(*graphPanel).initPanel(graphPanel);
	(*graphPanel).view.onMouseDown = onMouseDown;
	
	return graphPanel;
}

void initGraphPanel(GraphPanel *this)
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

void drawBackground(GraphPanel *this, int width, int height)
{
	Color color;
    color.red = 240;
    color.green = 240;
    color.blue = 240;
	
	drawRect((View *)this, 0, 0, width, height, color);
}

void drawGridView(GraphPanel *this, int width, int height)
{
	Color color;
    color.red = 200;
    color.green = 220;
    color.blue = 220;

	drawLine((View *)this, 10, 10, width-10, 10, color, LINE_THIN);
	drawLine((View *)this, width-10, 10, width-10, height-10, color, LINE_THIN);	

	int i=0;
	for (i=1;i<=12;++i) {
		drawLine((View *)this, 10, i*40+10, width-10, i*40+10, color, LINE_THIN);	
	}
	
	for (i=1;i<=6;++i) {
		drawLine((View *)this, i*120, 10, i*120, height-10, color, LINE_THIN);	
	}
}

void drawCoorindate(GraphPanel *this, int width, int height)
{
	Color color;
    color.red = 160;
    color.green = 160;
    color.blue = 180;

	drawLine((View *)this, 10, height-10, width-10, height-10, color, LINE_BOLD);
	drawLine((View *)this, 10, 10, 10, height-10, color, LINE_BOLD);

	int i=0;
	for (i=1;i<=12;++i) {
		drawLine((View *)this, 10, i*40+10, 14, i*40+10, color, LINE_THIN);	
	}
	
	for (i=1;i<=6;++i) {
		drawLine((View *)this, i*120, height-14, i*120, height-10, color, LINE_THIN);	
	}
}

void drawBorder(GraphPanel *this, int width, int height)
{
	Color color;
	color.red = 160;
    color.green = 160;
    color.blue = 160;
	
	drawLine((View *)this, 0, 0, width, 0, color, LINE_THIN);
	drawLine((View *)this, 0, 0, 0, height, color, LINE_THIN);
	drawLine((View *)this, 0, height-1, width, height-1, color, LINE_THIN);
	drawLine((View *)this, width-1, 0, width-1, height, color, LINE_THIN);
}

void onMouseDown(View *this, MouseEvent *event)
{
	showIntegerValue(898, 100, 50);
}
