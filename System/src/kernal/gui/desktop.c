#include "../type/type.h"
#include "sheet.h"
#include "color.h"
#include "image.h"
#include "desktop.h"

Sheet* prepareInfoBarSheet(Sheet *sheet)
{
    if (sheet != 0) {
        (*sheet).x = 0;
        (*sheet).y = 0;
        (*sheet).width = SCREEN_WIDTH;
        (*sheet).height = INFO_BAR_HEIGHT;
        (*sheet).buffer = (char *)allocMemoryInPage(SCREEN_WIDTH*INFO_BAR_HEIGHT*SCREEN_DENSITY);

        Color startColor;
        startColor.red = 250;
        startColor.green = 250;
        startColor.blue = 250;

        Color endColor;
        endColor.red = 220;
        endColor.green = 220;
        endColor.blue = 220;

        drawGradualVerticalRect((*sheet).buffer, sheet, 0, 0, SCREEN_WIDTH, INFO_BAR_HEIGHT, startColor, endColor);
    }
}

Sheet* prepareStartBarSheet(Sheet *sheet)
{
    if (sheet != 0) {
        (*sheet).x = 112;
        (*sheet).y = 300;
        (*sheet).width = START_BAR_WIDTH;
        (*sheet).height = START_BAR_HEIGHT;
        (*sheet).buffer = (char *)allocMemoryInPage(START_BAR_WIDTH*START_BAR_HEIGHT*SCREEN_DENSITY);

        resetSheet(sheet);

        Image *appIcon1 = loadImageFromStorage(0x8808);
        (*appIcon1).x = 80;
        (*appIcon1).y = 10;

        addImage(sheet, appIcon1);

        Image *appIcon2 = loadImageFromStorage(0x882e);
        (*appIcon2).x = 180;
        (*appIcon2).y = 10;

        addImage(sheet, appIcon2);

        Image *appIcon3 = loadImageFromStorage(0x8854);
        (*appIcon3).x = 280;
        (*appIcon3).y = 10;

        addImage(sheet, appIcon3);

        Image *appIcon4 = loadImageFromStorage(0x887a);
        (*appIcon4).x = 380;
        (*appIcon4).y = 10;

        addImage(sheet, appIcon4);
    }
}
