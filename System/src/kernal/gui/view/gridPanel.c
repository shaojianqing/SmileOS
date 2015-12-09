#include "../../const/const.h"
#include "../../type/type.h"
#include "../sheet.h"
#include "../color.h"
#include "../corner.h"
#include "view.h"
#include "../graphics.h"
#include "item/headerItem.h"
#include "item/gridDataItem.h"
#include "gridPanel.h"

static void initGridPanel(GridPanel *this, HeaderItem *itemList, u32 headerCount);

static void renderDataGrid(GridPanel *this, u32 dataSize, ItemRender itemRender);

static void onMouseDown(View *this, MouseEvent *event);

static void drawBackground(GridPanel *this, int width, int height);

static void drawHeaderInfo(GridPanel *this, int width, HeaderItem *itemList, u32 headerCount);

GridPanel *createGridPanel(int x, int y, int w, int h)
{
	GridPanel *gridPanel = (GridPanel *)alloc(sizeof(GridPanel));
	gridPanel = (GridPanel*)initWithViewFunction((View*)gridPanel, x, y, w, h);
	(*gridPanel).initPanel = initGridPanel;
	(*gridPanel).renderDataGrid = renderDataGrid;
	(*gridPanel).view.onMouseDown = onMouseDown;
	
	return gridPanel;
}

static void initGridPanel(GridPanel *this, HeaderItem *itemList, u32 headerCount)
{
	if (this!=null) {		
		int width = (*this).view.width;
		int height = (*this).view.height;
		
		drawBackground(this, width, height);
		drawHeaderInfo(this, width, itemList, headerCount);
	}
}

static void renderDataGrid(GridPanel *this, u32 dataSize, ItemRender itemRender)
{
	if (this!=null) {
		int width = (*this).view.width;
		View *panel = (View *)this;
		u32 i=0;
		for (i=0;i<dataSize;++i) {
			GridDataItem *gridDataItem = itemRender(this, i, width, GRID_DATA_ITEM_HEIGHT);
			View *item = (View *)gridDataItem;
			(*item).y = i*GRID_DATA_ITEM_HEIGHT + 28;
			(*panel).addSubView(panel, item);
		}		
	}
}

static void drawBackground(GridPanel *this, int width, int height)
{
	Color borderColor;
    borderColor.red = 160;
    borderColor.green = 160;
    borderColor.blue = 160;

	Color contentColor;
    contentColor.red = 250;
    contentColor.green = 250;
    contentColor.blue = 250;
	
	drawRect((View *)this, 0, 0, width, height, borderColor);
	drawRect((View *)this, 1, 1, width-2, height-2, contentColor);
}

static void drawHeaderInfo(GridPanel *this, int width, HeaderItem *itemList, u32 headerCount) 
{	
	Color startColor;
    startColor.red = 250;
    startColor.green = 250;
    startColor.blue = 250;

    Color endColor;
    endColor.red = 220;
    endColor.green = 220;
    endColor.blue = 220;

	Color borderColor;
    borderColor.red = 160;
    borderColor.green = 160;
    borderColor.blue = 160;

	Color separateColor;
    separateColor.red = 180;
    separateColor.green = 180;
    separateColor.blue = 180;
	
	drawGradualVerticalRect((View *)this, 1, 1, width-2, 28, startColor, endColor);
	drawLine((View *)this, 1, 28, width-2, 28, borderColor, LINE_THIN);

	Color textolor;
    textolor.red = 120;
    textolor.green = 120;
    textolor.blue = 120;

	u32 i = 0, x = 10;
	for (i=0;i<headerCount;++i) {
		HeaderItem *headerItem = itemList+i;
		int width = (*headerItem).width;
		char *name = (*headerItem).name;
		int worldCount = (*headerItem).wordCount;
		printString((View *)this, name, worldCount, x, 6, textolor, textolor);
		x+=width;
		drawLine((View *)this, x-10, 0, x-10, 28, separateColor, LINE_THIN);
	}
}

static void onMouseDown(View *this, MouseEvent *event)
{
}
