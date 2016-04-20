#include "../../const/const.h"
#include "../../type/type.h"
#include "../../memory/memory.h"
#include "../sheet.h"
#include "../color.h"
#include "event.h"
#include "view.h"

static bool addSubView(View *this, View *view);

static bool removeSubView(View *this, View *view);

static void clearView(View *this);

static void releaseView(View *this);

static void retainView(View *this);

static void deleteView(View *this);

static void refreshRectView(View *this);

static bool isInRange(View *view, MouseEvent *event);

static void setBackgroundColor(View *this, Color color);

static void processMouseDownEvent(View *this, MouseEvent *event);

View *createView(int x, int y, int width, int height)
{
	View *view = (View *)alloc(sizeof(View));	
	view = initWithViewFunction(view, x, y, width, height);
	(*view).clearView(view);
	return view;
}

View *initWithViewFunction(View *view, int x, int y, int width, int height) 
{
	(*view).buffer = (u8 *)allocPage(width*height*SCREEN_DENSITY);
	(*view).parentView = null;
	(*view).reference = 1;
	(*view).subViewNum = 0;	
	(*view).visible = TRUE;
	(*view).width = width;
	(*view).height = height;
	(*view).x = x;
	(*view).y = y;

	(*view).clearView = clearView;
	(*view).addSubView = addSubView;
	(*view).removeSubView = removeSubView;
	(*view).setBackgroundColor = setBackgroundColor;
	(*view).processMouseDownEvent = processMouseDownEvent;
	(*view).refreshRectView = refreshRectView;
	(*view).deleteView = deleteView;
	(*view).releaseView = releaseView;
	(*view).retainView = retainView;
	return view;
}

static bool addSubView(View *this, View *view)
{
	if (this!=null && view!=null) {
		int i=0, k=0;
		bool isContained=FALSE;
		for (i=0;i<(*this).subViewNum;++i) {
			if ((*this).subViewList[i]==view) {	
				isContained=TRUE;
				break;		
			}		
		}

		if (isContained) {
			View *currentView = view;
			for (k=i;k<(*this).subViewNum-1;++k) {
				(*this).subViewList[k] = (*this).subViewList[k+1];
			}
			(*this).subViewList[(*this).subViewNum-1] = currentView;
			(*view).z = (*this).subViewNum-1;
		} else {
			if ((*this).subViewNum<MAX_SUB_VIEW_NUM) {
				(*this).subViewList[(*this).subViewNum] = view;
				(*view).z = (*this).subViewNum;
				(*view).parentView = this;
				(*this).subViewNum++;
				(*view).retainView(view);	
			}		
		}
	}
	refreshViewRect(this, (*view).x, (*view).y, (*view).width, (*view).height, (*view).z);
}

static bool removeSubView(View *this, View *view)
{
	if (this!=null && view!=null) {
		int i=0, k=0;
		bool isContained=FALSE;
		for (i=0;i<(*this).subViewNum;++i) {
			if ((*this).subViewList[i]==view) {	
				isContained=TRUE;
				break;		
			}		
		}
		if (isContained) {
			View *currentView = view;
			for (k=i;k<(*this).subViewNum-1;++k) {
				(*this).subViewList[k] = (*this).subViewList[k+1];
			}
			(*this).subViewList[(*this).subViewNum-1] = null;
			(*this).subViewNum--;
			(*view).releaseView(view);
			refreshViewRect(this, (*view).x, (*view).y, (*view).width, (*view).height, (*view).z);
		}
	}
}

static void setBackgroundColor(View *this, Color color)
{
	if (this!=null && (*this).buffer!=null) {
		int width=(*this).width;
		int height=(*this).height;

		int i=0;
		for (i=0;i<width*height*SCREEN_DENSITY;i+=3) {
			*((*this).buffer+i)=color.blue;
			*((*this).buffer+i+1)=color.green;
			*((*this).buffer+i+2)=color.red;
		}
	}
}

static void clearView(View *this)
{
	if (this!=null && (*this).buffer!=null) {
		int width=(*this).width;
		int height=(*this).height;

		int i=0;
		for (i=0;i<width*height*SCREEN_DENSITY;++i) {
			*((*this).buffer+i)=0x00;
		}
	}
}

static void processMouseDownEvent(View *this, MouseEvent *event)
{
	if (this!=null && event!=null) {
		if ((*this).subViewNum>0) {
			int i=0;
			for (i=0;i<(*this).subViewNum;++i) {
				View *subView = (*this).subViewList[i];
				if (subView!=null && isInRange(subView, event)) {
					(*event).x=(*event).x-(*subView).x;
					(*event).y=(*event).y-(*subView).y;
					(*subView).processMouseDownEvent(subView, event);
				}			
			}	
		}

		if ((*this).onMouseDown!=null) {
			(*this).onMouseDown(this, event);
		}
	}
}

static bool isInRange(View *view, MouseEvent *event)
{
	if (view!=null && event!=null) {
		if ((*event).x>=(*view).x && (*event).x<(*view).x+(*view).width &&
			(*event).y>=(*view).y && (*event).y<(*view).y+(*view).height) {
			return TRUE;		
		}	
	}
	return FALSE;
}

static void refreshRectView(View *this)
{
	if (this!=null) {
		refreshViewRect(this, (*this).x, (*this).y, (*this).width, (*this).height, (*this).z);
	}
}

void refreshViewRect(View *this, int x, int y, int w, int h, int z)
{
	if (this!=null) {
		if ((*this).subViewNum>z) {
			int i=z, x0=0, y0=0, w0=0, h0=0;
			int xb=0, yb=0, wb=0, hb=0, dx=0, dy=0;
			View *subView=null;

			for (i=z;i<(*this).subViewNum;++i) {
				subView = (*this).subViewList[i];
				if ((*subView).visible==TRUE) {
					x0=(*subView).x;
					y0=(*subView).y;
					w0=(*subView).width;
					h0=(*subView).height;

					if (x>x0+w0 || y>y0+h0 || x0>x+w || y0>y+h) {
						continue;				
					} else {		
						if (x>=x0) {xb=x;wb=x0+w0-x;dx=x-x0;}
						if (x<x0) {xb=x0;wb=x+w-x0;dx=0;}
						if (y>=y0) {yb=y;hb=y0+h0-y;dy=y-y0;}
						if (y<y0) {yb=y0;hb=y+h-y0;dy=0;}
	
						int i=0,j=0;
						for (j=0;j<hb;++j) {
							for(i=0;i<wb;++i) {
								char blue = *((*subView).buffer+((j+dy)*(*subView).width+i+dx)*3);
				                char green = *((*subView).buffer+((j+dy)*(*subView).width+i+dx)*3+1);
				                char red = *((*subView).buffer+((j+dy)*(*subView).width+i+dx)*3+2);
				                if (blue != TRANSPARENT || green != TRANSPARENT || red != TRANSPARENT) {
									*((*this).buffer + ((yb+j)*(*this).width+xb+i)*3) = blue;
									*((*this).buffer + ((yb+j)*(*this).width+xb+i)*3+1) = green;	
									*((*this).buffer + ((yb+j)*(*this).width+xb+i)*3+2) = red;
				                }
							}					
						}
					}
				}
			}
		}
		if ((*this).parentView!=null) {			
			refreshViewRect((*this).parentView, (*this).x+x, (*this).y+y, w, h, (*this).z);			
		} else if ((*this).sheet!=null) {
			fillViewToSheetRect(this);
			refreshSheetRect((*this).sheet, (*this).x+x, (*this).y+y, w, h);
		}	
	}
}

void fillViewToSheetRect(View *this)
{
	if (this!=null && (*this).sheet!=null) {
		Sheet *sheet=(*this).sheet;

		int width=(*this).width, height=(*this).height;
		int sheetWidth = (*sheet).width;

		u32 x=0, y=0;
		for (y=0; y<height; ++y) {
		    for (x=0; x<width; ++x) {
		        *((*sheet).buffer+((y+(*this).y)*sheetWidth+x+(*this).x)*3) = *((*this).buffer+(y*width+x)*3);
		        *((*sheet).buffer+((y+(*this).y)*sheetWidth+x+(*this).x)*3+1) = *((*this).buffer+(y*width+x)*3+1);
		        *((*sheet).buffer+((y+(*this).y)*sheetWidth+x+(*this).x)*3+2) = *((*this).buffer+(y*width+x)*3+2);
		    }
		}	
	}
}

static void deleteView(View *this)
{
	if (this!=null) {
		if ((*this).buffer!=null) {
			u32 size = (*this).width*(*this).height*SCREEN_DENSITY;
			releasePage((u32)(*this).buffer, size);
			int i=0;
			View *currentView;
			for (i=0;i<(*this).subViewNum;++i) {
				currentView = (*this).subViewList[i];
				if (currentView!=null) {
					(*currentView).releaseView(currentView);		
				}	
			}
			if ((*this).sheet!=null) {
				Sheet *sheet = (*this).sheet;
				(*sheet).contentView = null;				
			}
		}
	}
}

static void releaseView(View *this)
{
	if (this!=null) {
		(*this).reference--;
		if ((*this).reference==0) {
			(*this).deleteView(this);	
		}
	}
}

static void retainView(View *this)
{
	if (this!=null) {
		(*this).reference++;
	}
}
