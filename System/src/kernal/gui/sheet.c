#include "../const/const.h"
#include "../type/type.h"
#include "video.h"
#include "image.h"
#include "sheet.h"

extern VideoModeInfo *videoModeInfo;

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

void initMouseSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		if ((*sheetManager).sheetNum<SHEET_NUM) {
			*((*sheetManager).sheets+(*sheetManager).sheetNum) = sheet;
			(*sheet).z = (*sheetManager).sheetNum;	
			(*sheetManager).sheetNum++;
			refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z);
			refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0, (*sheet).z);
		}
	}
}

void loadWindowSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		int sheetNum = (*sheetManager).sheetNum;
		if (sheetNum>=2 && sheetNum<SHEET_NUM) {			
			(*sheet).z = sheetNum-1;
			Sheet *topSheet = *((*sheetManager).sheets + sheetNum - 1);	
			(*topSheet).z = sheetNum;				
			*((*sheetManager).sheets + sheetNum) = topSheet;			
			*((*sheetManager).sheets + sheetNum - 1) = sheet;
			(*sheetManager).sheetNum++;
			refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z);
    		refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0, (*sheet).z);
		}
	}
}

void initBackgroundSheet(Sheet *sheet)
{
	if (sheet!=null) {
		SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
		(*sheet).z = 0;
		*((*sheetManager).sheets) = sheet;
		(*sheetManager).sheetNum++;
		refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z);
    	refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0, (*sheet).z);
	}
}

void loadSheet(Sheet *sheet, int z)
{
    SheetManager *sheetManager = (SheetManager *)SHEET_MANAGE_TABLE;
    (*sheet).z = z;
    *((*sheetManager).sheets + z) = sheet;
    (*sheetManager).sheetNum++;
    refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0, (*sheet).z);
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
                        if (blue != TRANSPARENT || green != TRANSPARENT || red != TRANSPARENT) {
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
                                *(vram + (vy*SCREEN_WIDTH + vx)*3) = blue;
                                *(vram + (vy*SCREEN_WIDTH + vx)*3 + 1) = green;
                                *(vram + (vy*SCREEN_WIDTH + vx)*3 + 2) = red;
                            }
                        }
                    }
                }
            }
        }
    }
}

void addImage(Sheet* sheet, Image* image)
{
    unsigned short height=(*image).height, width=(*image).width;
    unsigned int sheetWidth = (*sheet).width;

    unsigned int x=0, y=0;
    for (y=0; y<height; ++y) {
        for (x=0; x<width; ++x) {
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3) = *((*image).data+(y*80+x)*3);
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3+1) = *((*image).data+(y*80+x)*3+1);
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3+2) = *((*image).data+(y*80+x)*3+2);
        }
    }
}
