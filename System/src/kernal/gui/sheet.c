#include "../const/const.h"
#include "../type/type.h"
#include "color.h"
#include "view/event.h"
#include "view/view.h"
#include "video.h"
#include "image.h"
#include "sheet.h"

extern VideoModeInfo *videoModeInfo;

extern int currentDesktopIndex;

extern Sheet *mouse;

extern Sheet *startBarSheet;

extern Sheet *background;

extern Sheet *infoBarSheet;

MouseEvent mouseEvent;

void refreshSheetMap(int x1, int y1, int x2, int y2, int z1);

void refreshSheetSub(int x1, int y1, int x2, int y2, int z1, int z2);

void initSheetManagement()
{
    SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
    int i=0;
    for (i=0; i<SHEET_NUM; ++i) {
        Sheet *sheet = (Sheet *)((*sheetManager).sheetList+i);
        (*sheet).status = STATUS_SHEET_UNUSE;
    }
}

Sheet* prepareSheet()
{
    SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
    int i=0;
    for (i=0; i<SHEET_NUM; ++i) {
        Sheet *sheet = (Sheet *)((*sheetManager).sheetList+i);
        if ((*sheet).status == STATUS_SHEET_UNUSE) {
            (*sheet).status = STATUS_SHEET_USING;
            (*sheet).z = -1;
            return sheet;
        }
    }
    return null;
}

Sheet* getCurrentSheet(int x, int y)
{
	SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
	int i=currentDesktopIndex+1;
	for (; i>=0;--i) {
	    Sheet *sheet = (Sheet *)((*sheetManager).sheets[i]);
		if (sheet!=null) {	
			if ((x>=(*sheet).x && x<=(*sheet).x+(*sheet).width) &&
				(y>=(*sheet).y && y<=(*sheet).y+(*sheet).height)) {	
				return sheet;
			}
		}
	}
    return null;
}

void loadContentView(Sheet *sheet, View *view)
{
	if (sheet!=null && view!=null) {
		(*sheet).contentView = view;
		(*view).sheet = sheet;
		u32 width = (*view).width;
		u32 height = (*view).height;
		u32 sheetWidth = (*sheet).width;
		u32 i = 0,j = 0;
		for (j=0;j<height;++j) {
			for (i=0;i<width;++i) {
				*((*sheet).buffer+((j+(*view).y)*sheetWidth+i+(*view).x)*3) = *((*view).buffer+(j*80+i)*3);
		        *((*sheet).buffer+((j+(*view).y)*sheetWidth+i+(*view).x)*3+1) = *((*view).buffer+(j*80+i)*3+1);
		        *((*sheet).buffer+((j+(*view).y)*sheetWidth+i+(*view).x)*3+2) = *((*view).buffer+(j*80+i)*3+2);		
			}		
		}
		fillViewToSheetRect(view);
		refreshSheetRect(sheet, (*sheet).x, (*sheet).y, (*sheet).width, (*sheet).height);	
	}
}

void loadWindowSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		if (currentDesktopIndex<SHEET_NUM) {							
			(*sheet).z = currentDesktopIndex;
			(*sheetManager).sheets[currentDesktopIndex] = sheet;
			currentDesktopIndex++;
			reArrangeDesktopSheet();
			refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z);
   		    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0, (*sheet).z);
		}
	}
}

void setSheetTop(Sheet *sheet)
{
	if (sheet!=null) {	
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		if (currentDesktopIndex<SHEET_NUM) {
			if ((*sheet).z<currentDesktopIndex-1 && (*sheet).z>0) {
				int i=0;
				for (i=(*sheet).z;i<currentDesktopIndex-1;++i) {
					Sheet *sheetItem = (*sheetManager).sheets[i+1];
					(*sheetManager).sheets[i] = sheetItem;
					(*sheetItem).z=i;				
				}
				(*sheetManager).sheets[currentDesktopIndex-1] = sheet;
				(*sheet).z = currentDesktopIndex-1;	
			}
			refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z);
   		    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0, (*sheet).z);
		}
	}
}

bool isSheetTop(Sheet *sheet) 
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		if (currentDesktopIndex<SHEET_NUM) {						
			if ((*sheet).z>=currentDesktopIndex-1) {	
				return TRUE;			
			} else {
				return FALSE;
			}
		}
	}
	return FALSE;
}

void slideSheet(Sheet *sheet, int x, int y)
{
    SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
    if ((*sheet).z>=0) {
        int originX = (*sheet).x;
        int originY = (*sheet).y;
        (*sheet).x = x;
        (*sheet).y = y;
        refreshSheetMap(originX, originY, originX+(*sheet).width, originY+(*sheet).height, 0);
        refreshSheetMap(x, y, x+(*sheet).width, y+(*sheet).height, 0);
        refreshSheetSub(originX, originY, originX+(*sheet).width, originY+(*sheet).height, 0, (*sheet).z-1);
        refreshSheetSub(x, y, x+(*sheet).width, y+(*sheet).height, 0, (*sheet).z);
    }
}

void releaseSheet(Sheet *sheet)
{
    SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
}

void resetSheet(Sheet *sheet)
{
    if (sheet != 0) {
        u32 i=0;
        for (i=0; i<(*sheet).width*(*sheet).height*SCREEN_DENSITY; ++i) {
            *((*sheet).buffer+i) = 0x00;
        }
    }
}

void processSheetMouseDownEvent(Sheet *sheet, int x, int y)
{
	if (sheet!=null && (*sheet).contentView!=null) {
		View *contentView=(*sheet).contentView;
		mouseEvent.x=x-(*sheet).x;
		mouseEvent.y=y-(*sheet).y;
		if ((*contentView).processMouseDownEvent!=null) {
			(*contentView).processMouseDownEvent(contentView, &mouseEvent);
		}		
	}
}

void refreshSheetRect(Sheet *sheet, int x, int y, int w, int h)
{
	refreshSheetMap((*sheet).x + x, (*sheet).y + y, (*sheet).x + x + w, (*sheet).y + y + h, (*sheet).z);
    refreshSheetSub((*sheet).x + x, (*sheet).y + y, (*sheet).x + x + w, (*sheet).y + y + h, (*sheet).z, (*sheet).z);
}

void refreshSheetMap(int x1, int y1, int x2, int y2, int z1)
{
    if (x2>x1 && y2>y1) {
        SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
        u8 *map = (u8 *)MAP_ADDRESS;
        char *buffer;
        int x, y, xb1, yb1, xb2, yb2, vx, vy;
        u8 i=0, sid=0;

        if (x1<0) {
            x1=0;
        }
        if (y1<0) {
            y1=0;
        }
        if (x2>SCREEN_WIDTH) {
            x2=SCREEN_WIDTH;
        }
        if (y2>SCREEN_HEIGHT) {
            y2=SCREEN_HEIGHT;
        }

        for (i=z1; i<(*sheetManager).sheetNum; ++i) {
            Sheet *sheet = (*sheetManager).sheets[i];
            xb1 = x1 - (*sheet).x;
            yb1 = y1 - (*sheet).y;
            xb2 = x2 - (*sheet).x;
            yb2 = y2 - (*sheet).y;
            sid = i+1;

            if (xb1<0) {
                xb1=0;
            }
            if (yb1<0) {
                yb1=0;
            }
            if (xb2>(*sheet).width) {
                xb2=(*sheet).width;
            }
            if (yb2>(*sheet).height) {
                yb2=(*sheet).height;
            }

            if (xb2>xb1 && yb2>yb1) {
                for (y=yb1; y<yb2; ++y) {
                    vy = (*sheet).y + y;
                    for (x=xb1; x<xb2; ++x) {
                        vx = (*sheet).x + x;
                        char blue = *((*sheet).buffer + (y*(*sheet).width + x)*3);
                        char green = *((*sheet).buffer + (y*(*sheet).width + x)*3 + 1);
                        char red = *((*sheet).buffer + (y*(*sheet).width + x)*3 + 2);
                        if (blue!=TRANSPARENT || green!=TRANSPARENT || red!=TRANSPARENT) {
                            *(map+vy*SCREEN_WIDTH + vx) = sid;
                        }
                    }
                }
            }
        }
    }
}

void refreshSheetSub(int x1, int y1, int x2, int y2, int z1, int z2)
{
    if (x2>x1 && y2>y1) {
        SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
        u8 *vram = (u8 *)((*videoModeInfo).bufferAddress);
        u8 *map = (u8 *)MAP_ADDRESS;
        char *buffer;
        int x, y, xb1, yb1, xb2, yb2, vx, vy;
        u8 i=0, sid=0;

        if (x1<0) {
            x1=0;
        }
        if (y1<0) {
            y1=0;
        }
        if (x2>SCREEN_WIDTH) {
            x2=SCREEN_WIDTH;
        }
        if (y2>SCREEN_HEIGHT) {
            y2=SCREEN_HEIGHT;
        }

        for (i=z1; i<=z2; ++i) {
            Sheet *sheet = (*sheetManager).sheets[i];
            xb1 = x1 - (*sheet).x;
            yb1 = y1 - (*sheet).y;
            xb2 = x2 - (*sheet).x;
            yb2 = y2 - (*sheet).y;
            sid = i+1;

            if (xb1<0) {
                xb1=0;
            }
            if (yb1<0) {
                yb1=0;
            }
            if (xb2>(*sheet).width) {
                xb2=(*sheet).width;
            }
            if (yb2>(*sheet).height) {
                yb2=(*sheet).height;
            }
            if (xb2>xb1 && yb2>yb1) {
                for (y=yb1; y<yb2; ++y) {
                    vy = (*sheet).y + y;
                    for (x=xb1; x<xb2; ++x) {
                        vx = (*sheet).x + x;                        
                        if (*(map+vy*SCREEN_WIDTH + vx)==sid) {
							char blue = *((*sheet).buffer + (y*(*sheet).width + x)*3);
		                    char green = *((*sheet).buffer + (y*(*sheet).width + x)*3 + 1);
		                    char red = *((*sheet).buffer + (y*(*sheet).width + x)*3 + 2);
		                    if (blue != TRANSPARENT || green != TRANSPARENT || red != TRANSPARENT) {
								#if REAL						
		                            *(vram + (vy*SCREEN_WIDTH + vx)*4) = blue;
		                            *(vram + (vy*SCREEN_WIDTH + vx)*4 + 1) = green;
		                            *(vram + (vy*SCREEN_WIDTH + vx)*4 + 2) = red;
									*(vram + (vy*SCREEN_WIDTH + vx)*4 + 3) = 0xff;
								#else
									*(vram + (vy*SCREEN_WIDTH + vx)*3) = blue;
		                            *(vram + (vy*SCREEN_WIDTH + vx)*3 + 1) = green;
		                            *(vram + (vy*SCREEN_WIDTH + vx)*3 + 2) = red;
								#endif
                            }
                        }
                    }
                }
            }
        }
    }
}
