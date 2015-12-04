#include "../../const/const.h"
#include "../../type/type.h"
#include "../image.h"
#include "../color.h"
#include "../corner.h"
#include "../view/view.h"
#include "../view/style.h"
#include "../view/button.h"
#include "../event/buttonEvent.h"
#include "factory.h"

void selectButton(Factory *factory, Button *button);

void processEvent(Factory *factory, Button *button, MouseEvent *event);

void deselectButton(Factory *factory);

void doProcessEvent(Factory *factory);

void changeButtonStatus(Factory *factory);

void initFactory(Factory *factory, void (*onTimer)())
{
	if (factory!=null) {
		(*factory).selectFree=MAX_BUTTON_SIZE;
		(*factory).deselectFree=MAX_BUTTON_SIZE;
		(*factory).selectP=0;
		(*factory).selectQ=0;
		(*factory).deselectP=0;
		(*factory).deselectQ=0;
		(*factory).eventFree=MAX_BUTTON_EVENT;
		(*factory).eventP=0;
		(*factory).eventQ=0;		
	
		(*factory).onTimer = onTimer;
		(*factory).selectButton = selectButton;
		(*factory).processEvent = processEvent;
		(*factory).deselectButton = deselectButton;
		(*factory).doProcessEvent = doProcessEvent;
		(*factory).changeButtonStatus = changeButtonStatus;
	}	
}

void selectButton(Factory *factory, Button *button)
{
	if ((*factory).selectFree>0) {
		(*factory).selectButtonList[(*factory).selectP]=button;
		(*factory).selectP++;
		if ((*factory).selectP==MAX_BUTTON_SIZE) {
			(*factory).selectP=0;	
		}
		(*factory).selectFree--;
	}
}

void deselectButton(Factory *factory)
{
	Button *button;	
	if ((*factory).deselectFree<MAX_BUTTON_SIZE) {
		button = (*factory).deselectButtonList[(*factory).deselectQ];
		if (button!=null) {
			(*button).selectButton(button, FALSE);
		}
		(*factory).deselectQ++;
		if ((*factory).deselectQ==MAX_BUTTON_SIZE) {
			(*factory).deselectQ=0;
		}
		(*factory).deselectFree++;	
	}
}

void changeButtonStatus(Factory *factory)
{
	Button *button;
	if ((*factory).selectFree<MAX_BUTTON_SIZE) {
		button = (*factory).selectButtonList[(*factory).selectQ];
		(*factory).selectQ++;
		if ((*factory).selectQ==MAX_BUTTON_SIZE) {
			(*factory).selectQ=0;
		}
		(*factory).selectFree++;
		
		if (button!=null) {
			if ((*factory).deselectFree>0) {
				(*factory).deselectButtonList[(*factory).deselectP]=button;
				(*factory).deselectP++;
				if ((*factory).deselectP==MAX_BUTTON_SIZE) {
					(*factory).deselectP=0;	
				}
				(*factory).deselectFree--;
			}	
		}
	}	
}

void processEvent(Factory *factory, Button *button, MouseEvent *event)
{
	if (button!=null && event!=null && (*button).onMouseClick!=null) {
		if ((*factory).eventFree>0) {
			ButtonEvent *buttonEvent=&((*factory).buttonEventList[(*factory).eventP]);
			(*buttonEvent).button=button;
			(*buttonEvent).event=event;
			(*factory).eventP++;
			if ((*factory).eventP==MAX_BUTTON_EVENT) {
				(*factory).eventP=0;	
			}
			(*factory).eventFree--;
		}
	}
}

void doProcessEvent(Factory *factory)
{

	
	if ((*factory).eventFree<MAX_BUTTON_EVENT) {
		ButtonEvent (*buttonEvent) = &((*factory).buttonEventList[(*factory).eventQ]);
		if ((*buttonEvent).button!=null && (*buttonEvent).event!=null) {
			Button *button = (*buttonEvent).button;
			MouseEvent *event = (*buttonEvent).event;
			(*button).onMouseClick(button, event);
		}		
	
		(*factory).eventQ++;
		if ((*factory).eventQ==MAX_BUTTON_EVENT) {
			(*factory).eventQ=0;
		}
		(*factory).eventFree++;	
	}	
}

