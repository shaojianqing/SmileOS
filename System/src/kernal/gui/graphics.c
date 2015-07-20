#include "../const/const.h"
#include "../type/type.h"
#include "sheet.h"
#include "color.h"
#include "corner.h"
#include "graphics.h"

void drawRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color color)
{
    if (w>0 && h>0) {
        int i=0,j=0;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                *(buffer + (j*(*sheet).width+i)*3) = color.blue;
                *(buffer + (j*(*sheet).width+i)*3 + 1) = color.green;
                *(buffer + (j*(*sheet).width+i)*3 + 2) = color.red;
            }
        }
    }
}

void drawCornerRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color color, Corner corner)
{
    if (w>0 && h>0) {
        u32 i=0, j=0;
        u32 leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (j=y; j<y+h; ++j) {
            for (i=x+leftTop+leftBtm; i<x+w-rightTop-rightBtm; ++i) {
                *(buffer + (j*(*sheet).width+i)*3) = color.blue;
                *(buffer + (j*(*sheet).width+i)*3 + 1) = color.green;
                *(buffer + (j*(*sheet).width+i)*3 + 2) = color.red;
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

void drawRectAlpha(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color color, int alpha)
{
    if (w>0 && h>0) {
        int i=0,j=0;
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

void drawGradualVerticalRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor)
{
    if (w>0 && h>0) {
        int i=0,j=0;
        int distance = h;
        for (j=y; j<y+h; ++j) {
            for (i=x; i<x+w; ++i) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;
                *(buffer + (j*(*sheet).width+i)*3) = blue;
                *(buffer + (j*(*sheet).width+i)*3 + 1) = green;
                *(buffer + (j*(*sheet).width+i)*3 + 2) = red;
            }
        }
    }
}

void drawGradualVerticalRectAlpha(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor, int alpha)
{
    if (w>0 && h>0) {
        int i=0,j=0;
        int distance = h;
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

void drawGradualVerticalTrapezium(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha)
{
    if (w>2*r && h>0) {
        int i=0,j=0,k=r;
        int distance = h;
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

void drawGradualVerticalCornerRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor, Corner corner)
{
    if (w>0 && h>0) {
        u32 i=0,j=0;
        u32 distance = h;
        u32 leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (j=y; j<y+h; ++j) {
            for (i=x+leftTop+leftBtm; i<x+w-rightTop-rightBtm; ++i) {
                u32 red = startColor.red + (endColor.red - startColor.red)*(j-y)/distance;
                u32 green = startColor.green + (endColor.green - startColor.green)*(j-y)/distance;
                u32 blue =  startColor.blue + (endColor.blue - startColor.blue)*(j-y)/distance;

                *(buffer + (j*(*sheet).width+i)*3) = blue;
                *(buffer + (j*(*sheet).width+i)*3 + 1) = green;
                *(buffer + (j*(*sheet).width+i)*3 + 2) = red;
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

void drawCircle(u8 *buffer, Sheet *sheet, int x, int y, int radius, Color color)
{
    if (x>=radius && y>=radius) {
        int x1 = x-radius, y1 = y-radius;
        int x2 = x+radius, y2 = y+radius;
        int i=0,j=0;
        for (j=y1; j<y2; ++j) {
            for (i=x1; i<x2; ++i) {
                if ((i-x)*(i-x)+(j-y)*(j-y)<=radius*radius) {
                    *(buffer + (j*(*sheet).width+i)*3) = color.blue;
                	*(buffer + (j*(*sheet).width+i)*3 + 1) = color.green;
                	*(buffer + (j*(*sheet).width+i)*3 + 2) = color.red;
                }
            }
        }
    }
}

