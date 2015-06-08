
Sheet* prepareWindowSheet(Sheet *sheet)
{
    if (sheet != 0) {
        (*sheet).x = 340;
        (*sheet).y = 220;
        (*sheet).width = 600;
        (*sheet).height = 500;
        (*sheet).buffer = (char *)allocMemoryInPage((*sheet).width*		(*sheet).height*SCREEN_DENSITY);

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
        drawRect((*sheet).buffer, sheet, 0, 21, (*sheet).width, 500, mainBgColor);
        drawRect((*sheet).buffer, sheet, 1, 22, (*sheet).width-1, 498, mainColor);

        return sheet;
    }
}

void showInfo(Sheet *sheet, int x, int y, int key)
{
    Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;

    Color color;
    color.red = 220;
    color.green = 220;
    color.blue = 220;

    drawRect((*sheet).buffer, sheet, x, y, 500, 300, color);
    printInteger(sheet, key, x, y, mainColor);
    refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}

void showBufferInfo(Sheet *sheet, char *buffer)
{
	Color mainColor;
    mainColor.red = 30;
    mainColor.green = 30;
    mainColor.blue = 30;	
		
	int totalSize = 256, rowNum = 16, columnNum = 16;

	int x=0,y=0;
	for (y=0;y<columnNum;++y) {
		for (x=0;x<rowNum;++x) {
			char data= *(buffer+y*16+x);
			printHexByte(sheet, data, x*28+90, y*28+32, mainColor);
		}	
	}

	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
    refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}


