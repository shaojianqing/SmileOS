#include "../type/type.h"
#include "sheet.h"
#include "color.h"
#include "corner.h"
#include "graphics.h"

void drawRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color)
{
    if (x2>x1 && y2>y1) {
        int x=0,y=0;
        for (y=y1; y<y2; ++y) {
            for (x=x1; x<x2; ++x) {
                *(buffer + (y*(*sheet).width+x)*3) = color.blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = color.green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = color.red;
            }
        }
    }
}

void drawCornerRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color, Corner corner)
{
    if (x2>x1 && y2>y1) {
        unsigned int x=0, y=0;
        unsigned int leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (y=y1; y<y2; ++y) {
            for (x=x1+leftTop+leftBtm; x<x2-rightTop-rightBtm; ++x) {
                *(buffer + (y*(*sheet).width+x)*3) = color.blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = color.green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = color.red;
            }
            if (y<y1+corner.leftTop) {
                --leftTop;
            }
            if (y<y1+corner.rightTop) {
                --rightTop;
            }
            if (y>y2-corner.leftBtm-1) {
                ++leftBtm;
            }
            if (y>y2-corner.rightBtm-1) {
                ++rightBtm;
            }
        }
    }
}

void drawRectAlpha(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color, int alpha)
{
    if (x2>x1 && y2>y1) {
        int x=0,y=0;
        for (y=y1; y<y2; ++y) {
            for (x=x1; x<x2; ++x) {
                u8 red = color.red;
                u8 green = color.green;
                u8 blue = color.blue;

                u8 *sourceBlue = buffer + (y*(*sheet).width+x)*3;
                u8 *sourceGreen = buffer + (y*(*sheet).width+x)*3 + 1;
                u8 *sourceRed = buffer + (y*(*sheet).width+x)*3 + 2;

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

void drawGradualVerticalRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor)
{
    if (x2>x1 && y2>y1) {
        int x=0,y=0;
        int distance = y2-y1;
        for (y=y1; y<y2; ++y) {
            for (x=x1; x<x2; ++x) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;
                *(buffer + (y*(*sheet).width+x)*3) = blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = red;
            }
        }
    }
}

void drawGradualVerticalRectAlpha(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor, int alpha)
{
    if (x2>x1 && y2>y1) {
        int x=0,y=0;
        int distance = y2-y1;
        for (y=y1; y<y2; ++y) {
            for (x=x1; x<x2; ++x) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;

                u8 *sourceBlue = buffer + (y*(*sheet).width+x)*3;
                u8 *sourceGreen = buffer + (y*(*sheet).width+x)*3 + 1;
                u8 *sourceRed = buffer + (y*(*sheet).width+x)*3 + 2;

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

void drawGradualVerticalTrapezium(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, int r, Color startColor, Color endColor, int alpha)
{
    if (x2>x1+2*r && y2>y1) {
        int x=0,y=0,i=r;
        int distance = y2-y1;
        for (y=y1; y<y2; ++y) {
            for (x=x1+i; x<x2-i; ++x) {
                u8 red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                u8 green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                u8 blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;

                u8 *sourceBlue = buffer + (y*(*sheet).width+x)*3;
                u8 *sourceGreen = buffer + (y*(*sheet).width+x)*3 + 1;
                u8 *sourceRed = buffer + (y*(*sheet).width+x)*3 + 2;

                blue = blue*alpha/256 + (*sourceBlue)*(256-alpha)/256;
                green = green*alpha/256 + (*sourceGreen)*(256-alpha)/256;
                red = red*alpha/256 + (*sourceRed)*(256-alpha)/256;

                *sourceBlue = blue;
                *sourceGreen = green;
                *sourceRed = red;
            }
            --i;
        }
    }
}

void drawGradualVerticalCornerRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor, Corner corner)
{
    if (x2>x1 && y2>y1) {
        u32 x=0,y=0;
        u32 distance = y2-y1;
        u32 leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (y=y1; y<y2; ++y) {
            for (x=x1+leftTop+leftBtm; x<x2-rightTop-rightBtm; ++x) {
                u32 red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                u32 green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                u32 blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;

                *(buffer + (y*(*sheet).width+x)*3) = blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = red;
            }
            if (y<y1+corner.leftTop) {
                --leftTop;
            }
            if (y<y1+corner.rightTop) {
                --rightTop;
            }
            if (y>=y2-corner.leftBtm-1) {
                ++leftBtm;
            }
            if (y>=y2-corner.rightBtm-1) {
                ++rightBtm;
            }
        }
    }
}

void drawCircle(u8 *buffer, Sheet *sheet, int x0, int y0, int radius, Color color)
{
    if (x0>=radius && y0>=radius) {
        int x1 = x0-radius, y1 = y0-radius;
        int x2 = x0+radius, y2 = y0+radius;
        int x=0,y=0;
        for (y=y1; y<y2; ++y) {
            for (x=x1; x<x2; ++x) {
                if ((x-x0)*(x-x0)+(y-y0)*(y-y0)<=radius*radius) {
                    *(buffer + (y*(*sheet).width+x)*3) = color.blue;
                	*(buffer + (y*(*sheet).width+x)*3 + 1) = color.green;
                	*(buffer + (y*(*sheet).width+x)*3 + 2) = color.red;
                }
            }
        }
    }
}

