
Sheet* prepareWindowSheet(Sheet *sheet)
{
    if (sheet != 0)
    {
        (*sheet).x = 300;
        (*sheet).y = 200;
        (*sheet).width = 400;
        (*sheet).height = 300;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*(*sheet).height*SCREEN_DENSITY);

        resetSheet(sheet);

        Color startColor;
        startColor.red = 250;
        startColor.green = 250;
        startColor.blue = 250;

        Color endColor;
        endColor.red = 220;
        endColor.green = 220;
        endColor.blue = 220;

        Corner corner;
        corner.leftTop=2;
        corner.rightTop=2;
        corner.leftBtm=0;
        corner.rightBtm=0;

        Color mainBgColor;
        mainBgColor.red = 120;
        mainBgColor.green = 120;
        mainBgColor.blue = 120;

        Color mainColor;
        mainColor.red = 220;
        mainColor.green = 220;
        mainColor.blue = 220;

        drawCornerRect((*sheet).buffer, sheet, 0, 0, (*sheet).width, 21, mainBgColor, corner);
        drawGradualVerticalCornerRect((*sheet).buffer, sheet, 1, 1, (*sheet).width-1, 21, startColor, endColor, corner);
        drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 300, mainBgColor);
        drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-1, 298, mainColor);

        return sheet;
    }
}

void showInfo(Sheet *sheet, int count)
{

    Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;

    Color color;
    color.red = 220;
    color.green = 220;
    color.blue = 220;

    drawRect((*sheet).buffer, sheet, 20, 100, 300, 200, color);
    printInteger(sheet, count, 100, 100, mainColor);
    refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}
