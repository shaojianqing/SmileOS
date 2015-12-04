#include "../const/const.h"
#include "../type/type.h"
#include "image.h"
#include "view/view.h"
#include "sheet.h"
#include "color.h"
#include "corner.h"
#include "graphics.h"

void drawPoint(View *view, int x, int y, Color color)
{
	if (view!=null && (*view).buffer!=null) {
		if (x>0 && y>0) {
			u8 *buffer = (*view).buffer;
			*(buffer + (y*(*view).width+x)*3) = color.blue;
            *(buffer + (y*(*view).width+x)*3 + 1) = color.green;
            *(buffer + (y*(*view).width+x)*3 + 2) = color.red;
		}	
	}
}

void drawBoldPoint(View *view, int x, int y, Color color)
{
	if (view!=null && (*view).buffer!=null) {
		if (x>0 && y>0) {
			u8 *buffer = (*view).buffer;
			int i=0,j=0;
			for (j=y;j<y+2;++j) {
				for (i=x;i<x+1;++i) {
					*(buffer + (j*(*view).width+i)*3) = color.blue;
				    *(buffer + (j*(*view).width+i)*3 + 1) = color.green;
				    *(buffer + (j*(*view).width+i)*3 + 2) = color.red;			
				}			
			}
		}	
	}
}

void drawLine(View *view, int x1, int y1, int x2, int y2, Color color, int style)
{
	if (view!=null && (*view).buffer!=null) {
		if (x2>x1) {			
			int dx=x2-x1, dy=y2-y1, x=0, y=0;
			u8 *buffer = (*view).buffer;
			for (x=x1;x<=x2;++x) {
				y=(x-x1)*dy/dx +y1;
				*(buffer + (y*(*view).width+x)*3) = color.blue;
	            *(buffer + (y*(*view).width+x)*3 + 1) = color.green;
	            *(buffer + (y*(*view).width+x)*3 + 2) = color.red;
				if (style==LINE_BOLD) {
					*(buffer + ((y+1)*(*view).width+x)*3) = color.blue;
	            	*(buffer + ((y+1)*(*view).width+x)*3 + 1) = color.green;
	            	*(buffer + ((y+1)*(*view).width+x)*3 + 2) = color.red;
				}	
			}			
		} else if (x2==x1) {
			int x=x1, y=0;
			u8 *buffer = (*view).buffer;
			for (y=y1;y<=y2;++y) {
				*(buffer + (y*(*view).width+x)*3) = color.blue;
                *(buffer + (y*(*view).width+x)*3 + 1) = color.green;
                *(buffer + (y*(*view).width+x)*3 + 2) = color.red;
				if (style==LINE_BOLD) {
					*(buffer + (y*(*view).width+x+1)*3) = color.blue;
                	*(buffer + (y*(*view).width+x+1)*3 + 1) = color.green;
                	*(buffer + (y*(*view).width+x+1)*3 + 2) = color.red;
				}			
			}
		}	
	}
}

void drawImage(View *view, int x, int y, Image *image)
{
	if (view!=null && (*view).buffer!=null && image!=null) {
		u16 height=(*image).height, width=(*image).width;
		u32 viewWidth = (*view).width;

		u32 i=0, j=0;
		for (j=0; j<height; ++j) {
		    for (i=0; i<width; ++i) {
		        *((*view).buffer+((j+y)*viewWidth+i+x)*3) = *((*image).data+(j*width+i)*3);
		        *((*view).buffer+((j+y)*viewWidth+i+x)*3+1) = *((*image).data+(j*width+i)*3+1);
		        *((*view).buffer+((j+y)*viewWidth+i+x)*3+2) = *((*image).data+(j*width+i)*3+2);
		    }
		}
	}
}

void drawRect(View *view, int x, int y, int w, int h, Color color)
{
    if (w>0 && h>0) {
        int i=0,j=0;
		u8 *buffer = (*view).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                *(buffer + (j*(*view).width+i)*3) = color.blue;
                *(buffer + (j*(*view).width+i)*3 + 1) = color.green;
                *(buffer + (j*(*view).width+i)*3 + 2) = color.red;
            }
        }
    }
}

void drawCornerRect(View *view, int x, int y, int w, int h, Color color, Corner corner)
{
    if (w>0 && h>0) {
        u32 i=0, j=0;
		u8 *buffer = (*view).buffer;
        u32 leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (j=y; j<y+h; ++j) {
            for (i=x+leftTop+leftBtm; i<x+w-rightTop-rightBtm; ++i) {
                *(buffer + (j*(*view).width+i)*3) = color.blue;
                *(buffer + (j*(*view).width+i)*3 + 1) = color.green;
                *(buffer + (j*(*view).width+i)*3 + 2) = color.red;
            }
            if (j<y+corner.leftTop) {
                --leftTop;
            }
            if (j<y+corner.rightTop) {
                --rightTop;
            }
            if (j>y+h-corner.leftBtm-1) {
                ++leftBtm;
            }
            if (j>y+h-corner.rightBtm-1) {
                ++rightBtm;
            }
        }
    }
}

void drawRectAlpha(View *view, int x, int y, int w, int h, Color color, int alpha)
{
    if (w>0 && h>0) {
        int i=0,j=0;
		u8 *buffer = (*view).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                u8 red = color.red;
                u8 green = color.green;
                u8 blue = color.blue;

                u8 *sourceBlue = buffer + (j*(*view).width+i)*3;
                u8 *sourceGreen = buffer + (j*(*view).width+i)*3 + 1;
                u8 *sourceRed = buffer + (j*(*view).width+i)*3 + 2;

                blue = blue*alpha/256 + (*sourceBlue)*(256-alpha)/256;
                green = green*alpha/256 + (*sourceGreen)*(256-alpha)/256;
                red = red*alpha/256 + (*sourceRed)*(256-alpha)/256;

                *sourceBlue = blue;
                *sourceGreen = green;
                *sourceRed = red;
            }
        }
    }
}

void drawGradualVerticalRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor)
{
    if (w>0 && h>0) {
        int i=0,j=0;
        int distance = h;
		u8 *buffer = (*view).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;
                *(buffer + (j*(*view).width+i)*3) = blue;
                *(buffer + (j*(*view).width+i)*3 + 1) = green;
                *(buffer + (j*(*view).width+i)*3 + 2) = red;
            }
        }
    }
}

void drawGradualVerticalRectAlpha(View *view, int x, int y, int w, int h, Color startColor, Color endColor, int alpha)
{
    if (w>0 && h>0) {
        int i=0,j=0;
        int distance = h;
		u8 *buffer = (*view).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;

                u8 *sourceBlue = buffer + (j*(*view).width+i)*3;
                u8 *sourceGreen = buffer + (j*(*view).width+i)*3 + 1;
                u8 *sourceRed = buffer + (j*(*view).width+i)*3 + 2;

                blue = blue*alpha/256 + (*sourceBlue)*(256-alpha)/256;
                green = green*alpha/256 + (*sourceGreen)*(256-alpha)/256;
                red = red*alpha/256 + (*sourceRed)*(256-alpha)/256;

                *sourceBlue = blue;
                *sourceGreen = green;
                *sourceRed = red;
            }
        }
    }
}

void drawGradualVerticalTrapezium(View *view, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha)
{
    if (w>2*r && h>0) {
        int i=0,j=0,k=r;
        int distance = h;
		u8 *buffer = (*view).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x+k; i<x+w-k; ++i) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;

                u8 *sourceBlue = buffer + (j*(*view).width+i)*3;
                u8 *sourceGreen = buffer + (j*(*view).width+i)*3 + 1;
                u8 *sourceRed = buffer + (j*(*view).width+i)*3 + 2;

                blue = blue*alpha/256 + (*sourceBlue)*(256-alpha)/256;
                green = green*alpha/256 + (*sourceGreen)*(256-alpha)/256;
                red = red*alpha/256 + (*sourceRed)*(256-alpha)/256;

                *sourceBlue = blue;
                *sourceGreen = green;
                *sourceRed = red;
            }
            --k;
        }
    }
}

void drawGradualVerticalCornerRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor, Corner corner, int direction)
{
    if (w>0 && h>0) {
        u32 i=0,j=0,k=0;
        u32 distance = h;
		u8 *buffer = (*view).buffer;
        u32 leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (j=y; j<y+h; ++j) {
            for (i=x+leftTop+leftBtm; i<x+w-rightTop-rightBtm; ++i) {
                u32 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u32 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u32 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;
				if(direction==DIRECTION_UP) {
                	k=j;
				} else if (direction==DIRECTION_DOWN) {
					k=y+y+h-j-1;
				}
				*(buffer + (k*(*view).width+i)*3) = blue;
                *(buffer + (k*(*view).width+i)*3 + 1) = green;
                *(buffer + (k*(*view).width+i)*3 + 2) = red;
            }
            if (j<y+corner.leftTop) {
                --leftTop;
            }
            if (j<y+corner.rightTop) {
                --rightTop;
            }
            if (j>y+h-corner.leftBtm-1) {
                ++leftBtm;
            }
            if (j>y+h-corner.rightBtm-1) {
                ++rightBtm;
            }
        }
    }
}

void drawGradualHorizontalCornerRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor, Corner corner, int direction)
{
	if (w>0 && h>0) {
        u32 i=0,j=0,k=0;
        u32 distance = w;
		u8 *buffer = (*view).buffer;
        u32 leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (j=y; j<y+h; ++j) {
            for (i=x+leftTop+leftBtm; i<x+w-rightTop-rightBtm; ++i) {
                u32 red = startColor.red + (endColor.red - startColor.red)*(i-x)/distance;
                u32 green = startColor.green + (endColor.green - startColor.green)*(i-x)/distance;
                u32 blue =  startColor.blue + (endColor.blue - startColor.blue)*(i-x)/distance;
				if(direction==DIRECTION_UP) {
                	k=i;
				} else if (direction==DIRECTION_DOWN) {
					k=x+x+w-j-1;
				}
				*(buffer + (j*(*view).width+k)*3) = blue;
                *(buffer + (j*(*view).width+k)*3 + 1) = green;
                *(buffer + (j*(*view).width+k)*3 + 2) = red;
            }
            if (j<y+corner.leftTop) {
                --leftTop;
            }
            if (j<y+corner.rightTop) {
                --rightTop;
            }
            if (j>y+h-corner.leftBtm-1) {
                ++leftBtm;
            }
            if (j>y+h-corner.rightBtm-1) {
                ++rightBtm;
            }
        }
    }
}

void drawCircle(View *view, int x, int y, int radius, Color color)
{
    if (x>=radius && y>=radius) {
        int x1 = x-radius, y1 = y-radius;
        int x2 = x+radius, y2 = y+radius;
		u8 *buffer = (*view).buffer;
        int i=0,j=0;
        for (j=y1; j<y2; ++j) {
            for (i=x1; i<x2; ++i) {
                if ((i-x)*(i-x)+(j-y)*(j-y)<=radius*radius) {
                    *(buffer + (j*(*view).width+i)*3) = color.blue;
                	*(buffer + (j*(*view).width+i)*3 + 1) = color.green;
                	*(buffer + (j*(*view).width+i)*3 + 2) = color.red;
                }
            }
        }
    }
}

void drawGradualVerticalRectAlphaInSheet(Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor, int alpha)
{
	if (w>0 && h>0) {
        int i=0,j=0;
        int distance = h;
		u8 *buffer = (*sheet).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;

                u8 *sourceBlue = buffer + (j*(*sheet).width+i)*3;
                u8 *sourceGreen = buffer + (j*(*sheet).width+i)*3 + 1;
                u8 *sourceRed = buffer + (j*(*sheet).width+i)*3 + 2;

                blue = blue*alpha/256 + (*sourceBlue)*(256-alpha)/256;
                green = green*alpha/256 + (*sourceGreen)*(256-alpha)/256;
                red = red*alpha/256 + (*sourceRed)*(256-alpha)/256;

                *sourceBlue = blue;
                *sourceGreen = green;
                *sourceRed = red;
            }
        }
    }
}

void drawGradualVerticalTrapeziumInSheet(Sheet *sheet, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha)
{
	if (w>2*r && h>0) {
        int i=0,j=0,k=r;
        int distance = h;
		u8 *buffer = (*sheet).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x+k; i<x+w-k; ++i) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;

                u8 *sourceBlue = buffer + (j*(*sheet).width+i)*3;
                u8 *sourceGreen = buffer + (j*(*sheet).width+i)*3 + 1;
                u8 *sourceRed = buffer + (j*(*sheet).width+i)*3 + 2;

                blue = blue*alpha/256 + (*sourceBlue)*(256-alpha)/256;
                green = green*alpha/256 + (*sourceGreen)*(256-alpha)/256;
                red = red*alpha/256 + (*sourceRed)*(256-alpha)/256;

                *sourceBlue = blue;
                *sourceGreen = green;
                *sourceRed = red;
            }
            --k;
        }
    }
}

void drawRectAlphaInSheet(Sheet *sheet, int x, int y, int w, int h, Color color, int alpha)
{
	if (w>0 && h>0) {
        int i=0,j=0;
		u8 *buffer = (*sheet).buffer;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                u8 red = color.red;
                u8 green = color.green;
                u8 blue = color.blue;

                u8 *sourceBlue = buffer + (j*(*sheet).width+i)*3;
                u8 *sourceGreen = buffer + (j*(*sheet).width+i)*3 + 1;
                u8 *sourceRed = buffer + (j*(*sheet).width+i)*3 + 2;

                blue = blue*alpha/256 + (*sourceBlue)*(256-alpha)/256;
                green = green*alpha/256 + (*sourceGreen)*(256-alpha)/256;
                red = red*alpha/256 + (*sourceRed)*(256-alpha)/256;

                *sourceBlue = blue;
                *sourceGreen = green;
                *sourceRed = red;
            }
        }
    }
}

