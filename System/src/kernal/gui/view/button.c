#include "../../const/const.h"
#include "../../type/type.h"
#include "../../include/timing.h"
#include "view.h"
#include "../sheet.h"
#include "../color.h"
#include "../corner.h"
#include "../graphics.h"
#include "../event/buttonEvent.h"
#include "../factory/factory.h"
#include "style.h"
#include "event.h"
#include "button.h"

void selectButtonStatus(Button *this, bool select);

void onMouseDown(View *this, MouseEvent *event);

void resetViewBuffer(Button *this, int width, int height);

void drawAppearance(Button *this, int width, int height);

void drawDownAppearance(Button *this, int width, int height);

void drawButtonText(Button *this, char *string, int length, int width, int height);

Button *createButton(int x, int y, int w, int h, Factory *factory)
{
	Button *button = (Button *)alloc(sizeof(Button));
	button = (Button *)initWithViewFunction((View*)button, x, y, w, h);
	(*button).factory = factory;
	(*button).initButton = initButton;
	(*button).view.onMouseDown = onMouseDown;
	(*button).selectButton = selectButtonStatus;
	(*button).select = FALSE;

	return button;
}

void initButton(Button *this, char text[16], int length, ButtonStyleType buttonStyleType)
{
	if (this!=null) {		
		int width = (*this).view.width;
		int height = (*this).view.height;
		(*this).buttonStyleType = buttonStyleType;	

		resetViewBuffer(this, width, height);
		drawAppearance(this, width, height);		
		drawButtonText(this, text, length, width, height);
	}
}

void onMouseDown(View *this, MouseEvent *event)
{
	Button *button = (Button *)this;
	if ((*button).select==FALSE) {
		selectButtonStatus(button, TRUE);
		Factory *factory = (*button).factory;
		if (factory!=null) {
			(*factory).selectButton(factory, button);
			(*factory).processEvent(factory, button, event);
			Timer *timer = requestCurrentTimer(20, (*factory).onTimer);
		}
	}	
}

void selectButtonStatus(Button *this, bool select)
{
	if (this!=null) {
		char *text = (*this).title;
		int length = (*this).length;

		View *view = (View *)this;		

		int width = (*view).width;
		int height = (*view).height;

		if (select==TRUE) {
			drawDownAppearance(this, width, height);
			(*this).select=TRUE;		
		} else {
			drawAppearance(this, width, height);
			(*this).select=FALSE;
		}
		drawButtonText(this, text, length, width, height);
		View *parent = (*view).parentView;
		refreshViewRect(parent, (*view).x, (*view).y, (*view).width, (*view).height, (*parent).z);	
	}
} 

void resetViewBuffer(Button *this, int width, int height)
{
	u8 *buffer = (*this).view.buffer;
	int i=0;
	for (i=0;i<width*height*3;++i) {
		*(buffer+i) = 0x00;		
	}
}

void drawAppearance(Button *this, int width, int height)
{
	ButtonStyle *buttonStyle;
	ButtonStyleType buttonStyleType=(*this).buttonStyleType;
	if (buttonStyleType!=null) {
		buttonStyle=buttonStyleType();
			
	}

	drawCornerRect((View *)this, 0, 0, width, height, (*buttonStyle).borderColor, (*buttonStyle).corner);
    drawGradualVerticalCornerRect((View *)this, 1, 1, width-2, height-2, (*buttonStyle).startColor, (*buttonStyle).endColor, (*buttonStyle).corner, DIRECTION_DOWN);
}

void drawDownAppearance(Button *this, int width, int height)
{
	ButtonStyle *buttonStyle;
	ButtonStyleType buttonStyleType=(*this).buttonStyleType;
	if (buttonStyleType!=null) {
		buttonStyle=buttonStyleType();	
	}

	drawCornerRect((View *)this, 0, 0, width, height, (*buttonStyle).borderColor, (*buttonStyle).corner);
    drawGradualVerticalCornerRect((View *)this, 1, 1, width-2, height-2, (*buttonStyle).startDownColor, (*buttonStyle).endDownColor, (*buttonStyle).corner, DIRECTION_DOWN);
}

void drawButtonText(Button *this, char *string, int length, int width, int height)
{
	ButtonStyle *buttonStyle;
	ButtonStyleType buttonStyleType=(*this).buttonStyleType;
	if (buttonStyleType!=null) {
		buttonStyle=buttonStyleType();	
	}

	int i=0;
	int limit = (length<16?length:16);
	(*this).length = limit;
	for (i=0;i<limit;++i) {
		(*this).title[i] = *(string+i);
	}	

	printString((View *)this, (*this).title, (*this).length, 38, 8, (*buttonStyle).textColor);
}
