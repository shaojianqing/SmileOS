#include "../../const/const.h"
#include "../../type/type.h"
#include "../color.h"
#include "../corner.h"
#include "style.h"

ButtonStyle buttonStyleDarkRed;

ButtonStyle buttonStyleLightGray;

ButtonStyle buttonStyleLightBlue;

ButtonStyle buttonStyleDarkBlue;

ButtonStyle buttonStyleDarkOrange;

ButtonStyle buttonStyleBlackBlue;

ButtonStyle* ButtonStyleDarkRed()
{
	buttonStyleDarkRed.borderColor.red = 240;
    buttonStyleDarkRed.borderColor.green = 40;
    buttonStyleDarkRed.borderColor.blue = 60;

	buttonStyleDarkRed.startColor.red = 220;
    buttonStyleDarkRed.startColor.green = 80;
    buttonStyleDarkRed.startColor.blue = 60;

	buttonStyleDarkRed.endColor.red = 250;
    buttonStyleDarkRed.endColor.green = 80;
	buttonStyleDarkRed.endColor.blue = 60;

	buttonStyleDarkRed.startDownColor.red = 200;
    buttonStyleDarkRed.startDownColor.green = 60;
    buttonStyleDarkRed.startDownColor.blue = 40;

	buttonStyleDarkRed.endDownColor.red = 220;
    buttonStyleDarkRed.endDownColor.green = 60;
    buttonStyleDarkRed.endDownColor.blue = 40;

	buttonStyleDarkRed.textColor.red = 240;
    buttonStyleDarkRed.textColor.green = 240;
    buttonStyleDarkRed.textColor.blue = 240;

	buttonStyleDarkRed.corner.leftTop = 2;
	buttonStyleDarkRed.corner.rightTop = 2;
	buttonStyleDarkRed.corner.leftBtm = 2;
	buttonStyleDarkRed.corner.rightBtm = 2;

	return &buttonStyleDarkRed;
}

ButtonStyle* ButtonStyleLightGray()
{
	buttonStyleLightGray.borderColor.red = 160;
    buttonStyleLightGray.borderColor.green = 160;
    buttonStyleLightGray.borderColor.blue = 160;

	buttonStyleLightGray.startColor.red = 180;
    buttonStyleLightGray.startColor.green = 180;
    buttonStyleLightGray.startColor.blue = 180;

	buttonStyleLightGray.endColor.red = 220;
    buttonStyleLightGray.endColor.green = 220;
    buttonStyleLightGray.endColor.blue = 220;

	buttonStyleLightGray.startDownColor.red = 160;
    buttonStyleLightGray.startDownColor.green = 160;
    buttonStyleLightGray.startDownColor.blue = 160;

	buttonStyleLightGray.endDownColor.red = 200;
    buttonStyleLightGray.endDownColor.green = 200;
    buttonStyleLightGray.endDownColor.blue = 200;

	buttonStyleLightGray.textColor.red = 88;
    buttonStyleLightGray.textColor.green = 88;
    buttonStyleLightGray.textColor.blue = 88;

	buttonStyleLightGray.corner.leftTop = 2;
	buttonStyleLightGray.corner.rightTop = 2;
	buttonStyleLightGray.corner.leftBtm = 2;
	buttonStyleLightGray.corner.rightBtm = 2;

	return &buttonStyleLightGray;
}

ButtonStyle* ButtonStyleLightBlue()
{
	buttonStyleLightBlue.borderColor.red = 160;
    buttonStyleLightBlue.borderColor.green = 160;
    buttonStyleLightBlue.borderColor.blue = 160;

	buttonStyleLightBlue.startColor.red = 80;
    buttonStyleLightBlue.startColor.green = 160;
    buttonStyleLightBlue.startColor.blue = 180;

	buttonStyleLightBlue.endColor.red = 120;
    buttonStyleLightBlue.endColor.green = 200;
    buttonStyleLightBlue.endColor.blue = 220;

	buttonStyleLightBlue.startDownColor.red = 160;
    buttonStyleLightBlue.startDownColor.green = 160;
    buttonStyleLightBlue.startDownColor.blue = 160;

	buttonStyleLightBlue.endDownColor.red = 200;
    buttonStyleLightBlue.endDownColor.green = 200;
    buttonStyleLightBlue.endDownColor.blue = 200;

	buttonStyleLightBlue.textColor.red = 240;
    buttonStyleLightBlue.textColor.green = 240;
    buttonStyleLightBlue.textColor.blue = 240;

	buttonStyleLightBlue.corner.leftTop = 2;
	buttonStyleLightBlue.corner.rightTop = 2;
	buttonStyleLightBlue.corner.leftBtm = 2;
	buttonStyleLightBlue.corner.rightBtm = 2;

	return &buttonStyleLightBlue;
}

ButtonStyle* ButtonStyleDarkBlue()
{
	buttonStyleDarkBlue.borderColor.red = 70;
    buttonStyleDarkBlue.borderColor.green = 160;
    buttonStyleDarkBlue.borderColor.blue = 220;

	buttonStyleDarkBlue.startColor.red = 60;
    buttonStyleDarkBlue.startColor.green = 140;
    buttonStyleDarkBlue.startColor.blue = 210;

	buttonStyleDarkBlue.endColor.red = 100;
    buttonStyleDarkBlue.endColor.green = 180;
    buttonStyleDarkBlue.endColor.blue = 250;

	buttonStyleDarkBlue.startDownColor.red = 20;
    buttonStyleDarkBlue.startDownColor.green = 100;
    buttonStyleDarkBlue.startDownColor.blue = 170;

	buttonStyleDarkBlue.endDownColor.red = 60;
    buttonStyleDarkBlue.endDownColor.green = 140;
    buttonStyleDarkBlue.endDownColor.blue = 210;

	buttonStyleDarkBlue.textColor.red = 240;
    buttonStyleDarkBlue.textColor.green = 240;
    buttonStyleDarkBlue.textColor.blue = 240;

	buttonStyleDarkBlue.corner.leftTop = 2;
	buttonStyleDarkBlue.corner.rightTop = 2;
	buttonStyleDarkBlue.corner.leftBtm = 2;
	buttonStyleDarkBlue.corner.rightBtm = 2;

	return &buttonStyleDarkBlue;
}

ButtonStyle* ButtonStyleDarkOrange()
{
	buttonStyleDarkOrange.borderColor.red = 160;
    buttonStyleDarkOrange.borderColor.green = 100;
    buttonStyleDarkOrange.borderColor.blue = 60;

	buttonStyleDarkOrange.startColor.red = 180;
    buttonStyleDarkOrange.startColor.green = 120;
    buttonStyleDarkOrange.startColor.blue = 50;

	buttonStyleDarkOrange.endColor.red = 200;
    buttonStyleDarkOrange.endColor.green = 140;
    buttonStyleDarkOrange.endColor.blue = 70;

	buttonStyleDarkOrange.startDownColor.red = 160;
    buttonStyleDarkOrange.startDownColor.green = 100;
    buttonStyleDarkOrange.startDownColor.blue = 30;

	buttonStyleDarkOrange.endDownColor.red = 180;
    buttonStyleDarkOrange.endDownColor.green = 120;
    buttonStyleDarkOrange.endDownColor.blue = 50;

	buttonStyleDarkOrange.textColor.red = 240;
    buttonStyleDarkOrange.textColor.green = 240;
    buttonStyleDarkOrange.textColor.blue = 240;

	buttonStyleDarkOrange.corner.leftTop = 2;
	buttonStyleDarkOrange.corner.rightTop = 2;
	buttonStyleDarkOrange.corner.leftBtm = 2;
	buttonStyleDarkOrange.corner.rightBtm = 2;

	return &buttonStyleDarkOrange;
}

ButtonStyle* ButtonStyleBlackBlue()
{
	buttonStyleBlackBlue.borderColor.red = 40;
    buttonStyleBlackBlue.borderColor.green = 60;
    buttonStyleBlackBlue.borderColor.blue = 80;

	buttonStyleBlackBlue.startColor.red = 20;
    buttonStyleBlackBlue.startColor.green = 40;
    buttonStyleBlackBlue.startColor.blue = 60;

	buttonStyleBlackBlue.endColor.red = 40;
    buttonStyleBlackBlue.endColor.green = 60;
    buttonStyleBlackBlue.endColor.blue = 80;

	buttonStyleBlackBlue.startDownColor.red = 10;
    buttonStyleBlackBlue.startDownColor.green = 30;
    buttonStyleBlackBlue.startDownColor.blue = 50;

	buttonStyleBlackBlue.endDownColor.red = 30;
    buttonStyleBlackBlue.endDownColor.green = 50;
    buttonStyleBlackBlue.endDownColor.blue = 70;

	buttonStyleBlackBlue.textColor.red = 200;
    buttonStyleBlackBlue.textColor.green = 200;
    buttonStyleBlackBlue.textColor.blue = 200;

	buttonStyleBlackBlue.corner.leftTop = 2;
	buttonStyleBlackBlue.corner.rightTop = 2;
	buttonStyleBlackBlue.corner.leftBtm = 2;
	buttonStyleBlackBlue.corner.rightBtm = 2;

	return &buttonStyleBlackBlue;
}
