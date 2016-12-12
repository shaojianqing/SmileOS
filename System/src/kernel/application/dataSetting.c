#include "../const/const.h"
#include "../type/type.h"
#include "../gui/color.h"
#include "../gui/corner.h"
#include "../gui/sheet.h"
#include "../gui/image.h"
#include "../gui/view/view.h"
#include "../gui/view/style.h"
#include "../gui/graphics.h"
#include "../gui/view/graphPanel.h"
#include "dataSetting.h"

BarData barDataList[barDataCount];

LineData lineDataList[lineDataCount];

void prepareBarDataList()
{
	BarData *barData = barDataList;	

	(*barData).startColor.red = 60;
	(*barData).startColor.green = 140;
	(*barData).startColor.blue = 210;

	(*barData).endColor.red = 100;
	(*barData).endColor.green = 180;
	(*barData).endColor.blue = 250;

	(*barData).corner.leftTop = 2;
	(*barData).corner.rightTop = 2;
	(*barData).corner.leftBtm = 0;
	(*barData).corner.rightBtm = 0;

	(*barData).value = 300;

	barData = barDataList+1;	

	(*barData).startColor.red = 210;
	(*barData).startColor.green = 60;
	(*barData).startColor.blue = 140;

	(*barData).endColor.red = 250;
	(*barData).endColor.green = 100;
	(*barData).endColor.blue = 180;

	(*barData).corner.leftTop = 2;
	(*barData).corner.rightTop = 2;
	(*barData).corner.leftBtm = 0;
	(*barData).corner.rightBtm = 0;

	(*barData).value = 340;

	barData = barDataList+2;

	(*barData).startColor.red = 80;
	(*barData).startColor.green = 200;
	(*barData).startColor.blue = 140;

	(*barData).endColor.red = 120;
	(*barData).endColor.green = 240;
	(*barData).endColor.blue = 180;

	(*barData).corner.leftTop = 2;
	(*barData).corner.rightTop = 2;
	(*barData).corner.leftBtm = 0;
	(*barData).corner.rightBtm = 0;

	(*barData).value = 340;

	barData = barDataList+3;

	(*barData).startColor.red = 140;
	(*barData).startColor.green = 160;
	(*barData).startColor.blue = 60;

	(*barData).endColor.red = 200;
	(*barData).endColor.green = 200;
	(*barData).endColor.blue = 80;

	(*barData).corner.leftTop = 2;
	(*barData).corner.rightTop = 2;
	(*barData).corner.leftBtm = 0;
	(*barData).corner.rightBtm = 0;

	(*barData).value = 360;

	barData = barDataList+4;

	(*barData).startColor.red = 220;
	(*barData).startColor.green = 60;
	(*barData).startColor.blue = 60;

	(*barData).endColor.red = 250;
	(*barData).endColor.green = 100;
	(*barData).endColor.blue = 80;

	(*barData).corner.leftTop = 2;
	(*barData).corner.rightTop = 2;
	(*barData).corner.leftBtm = 0;
	(*barData).corner.rightBtm = 0;

	(*barData).value = 400;

	barData = barDataList+5;

	(*barData).startColor.red = 200;
	(*barData).startColor.green = 60;
	(*barData).startColor.blue = 200;

	(*barData).endColor.red = 240;
	(*barData).endColor.green = 80;
	(*barData).endColor.blue = 240;

	(*barData).corner.leftTop = 2;
	(*barData).corner.rightTop = 2;
	(*barData).corner.leftBtm = 0;
	(*barData).corner.rightBtm = 0;

	(*barData).value = 380;
}

void prepareLineDataList()
{
	LineData *lineData = lineDataList;	

	(*lineData).color.red = 60;
	(*lineData).color.green = 140;
	(*lineData).color.blue = 210;

	(*lineData).value = 200;

	lineData = lineDataList+1;

	(*lineData).color.red = 200;
	(*lineData).color.green = 120;
	(*lineData).color.blue = 240;

	(*lineData).value = 300;

	lineData = lineDataList+2;

	(*lineData).color.red = 220;
	(*lineData).color.green = 200;
	(*lineData).color.blue = 120;

	(*lineData).value = 360;

	lineData = lineDataList+3;

	(*lineData).color.red = 30;
	(*lineData).color.green = 200;
	(*lineData).color.blue = 220;

	(*lineData).value = 320;

	lineData = lineDataList+4;

	(*lineData).color.red = 120;
	(*lineData).color.green = 180;
	(*lineData).color.blue = 220;

	(*lineData).value = 380;

	lineData = lineDataList+5;

	(*lineData).color.red = 220;
	(*lineData).color.green = 120;
	(*lineData).color.blue = 180;

	(*lineData).value = 360;
}

void drawBarGraph(GraphPanel *this)
{
	if (this!=null && (*this).canvas!=null) {
		View *canvas = (*this).canvas;
		(*canvas).clearView(canvas);

		prepareBarDataList();

		u32 height = (*canvas).height - ORIGIN_Y;

		u32 i=0;
		for (i=0;i<barDataCount;++i) {
			BarData barData = barDataList[i];

			printInteger(canvas, barData.value, 120*i+125, height - barData.value - 20, 
						 barData.startColor, barData.startColor);
			drawCornerRect(canvas, 120*i+100, height - barData.value, 40, 
						   barData.value, barData.startColor, barData.corner);
			drawGradualHorizontalCornerRect(canvas, 120*i+100+1, height - barData.value+1, 38, 
											barData.value, barData.startColor,
											barData.endColor, barData.corner, DIRECTION_UP);
		}

		View *view = (View *)this;
		(*view).refreshRectView(view);
		(*canvas).refreshRectView(canvas);
	}
}

void drawLineGraph(GraphPanel *this)
{
	if (this!=null && (*this).canvas!=null) {
		View *canvas = (*this).canvas;
		(*canvas).clearView(canvas);

		u32 height = (*canvas).height - ORIGIN_Y;

		prepareLineDataList();
		
		u32 i=0;
		for (i=0;i<lineDataCount;++i) {
			LineData lineData = lineDataList[i];

			if (i<lineDataCount-1) {
				int x1 = 120*i+125;
				int y1 = height - lineData.value;

				LineData lineData2 = lineDataList[i+1];
				int x2 = 120*(i+1)+125;
				int y2 = height - lineData2.value;

				drawLine(canvas, x1, y1, x2, y2, lineData.color, LINE_BOLD);		
			}

			printInteger(canvas, lineData.value, 120*i+125, height - lineData.value - 30, 
						 lineData.color, lineData.color);
			drawCircle(canvas, 120*i+125, height - lineData.value, 6, lineData.color);	
		}

		View *view = (View *)this;
		(*view).refreshRectView(view);
		(*canvas).refreshRectView(canvas);
	}
}
