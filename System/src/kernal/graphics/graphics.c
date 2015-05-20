Color makeColor(unsigned char red, unsigned char green, unsigned char blue)
{
    Color color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    return color;
}

void drawRect(unsigned char *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color)
{
    if (x2>x1 && y2>y1)
    {
        int x=0,y=0;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1; x<x2; ++x)
            {
                *(buffer + (y*(*sheet).width+x)*3) = color.blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = color.green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = color.red;
            }
        }
    }
}

void drawCornerRect(unsigned char *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color, Corner corner)
{
    if (x2>x1 && y2>y1)
    {
        unsigned int x=0, y=0;
        unsigned int leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1+leftTop+leftBtm; x<x2-rightTop-rightBtm; ++x)
            {
                *(buffer + (y*(*sheet).width+x)*3) = color.blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = color.green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = color.red;
            }
            if (y<y1+corner.leftTop)
            {
                --leftTop;
            }
            if (y<y1+corner.rightTop)
            {
                --rightTop;
            }
            if (y>y2-corner.leftBtm-1)
            {
                ++leftBtm;
            }
            if (y>y2-corner.rightBtm-1)
            {
                ++rightBtm;
            }
        }
    }
}

void drawRectAlpha(unsigned char *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color, int alpha)
{
    if (x2>x1 && y2>y1)
    {
        int x=0,y=0;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1; x<x2; ++x)
            {
                unsigned char red = color.red;
                unsigned char green = color.green;
                unsigned char blue = color.blue;

                unsigned char *sourceBlue = buffer + (y*(*sheet).width+x)*3;
                unsigned char *sourceGreen = buffer + (y*(*sheet).width+x)*3 + 1;
                unsigned char *sourceRed = buffer + (y*(*sheet).width+x)*3 + 2;

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

void drawGradualVerticalRect(unsigned char *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor)
{
    if (x2>x1 && y2>y1)
    {
        int x=0,y=0;
        int distance = y2-y1;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1; x<x2; ++x)
            {
                unsigned char red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                unsigned char green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                unsigned char blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;
                *(buffer + (y*(*sheet).width+x)*3) = blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = red;
            }
        }
    }
}

void drawGradualVerticalRectAlpha(unsigned char *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor, int alpha)
{
    if (x2>x1 && y2>y1)
    {
        int x=0,y=0;
        int distance = y2-y1;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1; x<x2; ++x)
            {
                unsigned char red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                unsigned char green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                unsigned char blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;

                unsigned char *sourceBlue = buffer + (y*(*sheet).width+x)*3;
                unsigned char *sourceGreen = buffer + (y*(*sheet).width+x)*3 + 1;
                unsigned char *sourceRed = buffer + (y*(*sheet).width+x)*3 + 2;

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

void drawGradualVerticalTrapezium(unsigned char *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, int r, Color startColor, Color endColor, int alpha)
{
    if (x2>x1+2*r && y2>y1)
    {
        int x=0,y=0,i=r;
        int distance = y2-y1;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1+i; x<x2-i; ++x)
            {
                unsigned char red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                unsigned char green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                unsigned char blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;

                unsigned char *sourceBlue = buffer + (y*(*sheet).width+x)*3;
                unsigned char *sourceGreen = buffer + (y*(*sheet).width+x)*3 + 1;
                unsigned char *sourceRed = buffer + (y*(*sheet).width+x)*3 + 2;

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

void drawGradualVerticalCornerRect(unsigned char *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor, Corner corner)
{
    if (x2>x1 && y2>y1)
    {
        unsigned int x=0,y=0;
        unsigned int distance = y2-y1;
        unsigned int leftTop = corner.leftTop, rightTop = corner.rightTop, leftBtm = 0, rightBtm = 0;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1+leftTop+leftBtm; x<x2-rightTop-rightBtm; ++x)
            {
                unsigned char red = startColor.red + (endColor.red - startColor.red)*(y-y1)/distance;
                unsigned char green = startColor.green + (endColor.green - startColor.green)*(y-y1)/distance;
                unsigned char blue =  startColor.blue + (endColor.blue - startColor.blue)*(y-y1)/distance;

                *(buffer + (y*(*sheet).width+x)*3) = blue;
                *(buffer + (y*(*sheet).width+x)*3 + 1) = green;
                *(buffer + (y*(*sheet).width+x)*3 + 2) = red;
            }
            if (y<y1+corner.leftTop)
            {
                --leftTop;
            }
            if (y<y1+corner.rightTop)
            {
                --rightTop;
            }
            if (y>=y2-corner.leftBtm-1)
            {
                ++leftBtm;
            }
            if (y>=y2-corner.rightBtm-1)
            {
                ++rightBtm;
            }
        }
    }
}

void drawCircle(int x0, int y0, int radius, Color color)
{
    if (x0>=radius && y0>=radius)
    {
        int x1 = x0-radius, y1 = y0-radius;
        int x2 = x0+radius, y2 = y0+radius;
        int x=0,y=0;
        for (y=y1; y<y2; ++y)
        {
            for (x=x1; x<x2; ++x)
            {
                if ((x-x0)*(x-x0)+(y-y0)*(y-y0)<=radius*radius)
                {
                    writeVRAM((y*1024+x)*3, color.blue, color.green, color.red);
                }
            }
        }
    }
}

