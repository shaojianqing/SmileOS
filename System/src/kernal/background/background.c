#define START_BAR_BG_HEIGHT 80

Sheet* prepareBackgroundSheet(Sheet *sheet)
{
    if (sheet != 0) {
        (*sheet).x = 0;
        (*sheet).y = 0;
        (*sheet).width = SCREEN_WIDTH;
        (*sheet).height = SCREEN_HEIGHT;
        u32 size = SCREEN_WIDTH*SCREEN_HEIGHT*SCREEN_DENSITY+8;
        Image *bgImage = loadImageFromStorage(0x4000);        
        (*sheet).buffer = (*bgImage).data;

        Color startColor;
        startColor.red = 250;
        startColor.green = 250;
        startColor.blue = 250;

        Color endColor;
        endColor.red = 220;
        endColor.green = 220;
        endColor.blue = 220;

        Color sepColor;
        sepColor.red = 240;
        sepColor.green = 240;
        sepColor.blue = 240;

        drawGradualVerticalRectAlpha((*sheet).buffer, sheet, 0, 0, SCREEN_WIDTH, 24, startColor, endColor, 160);

        drawGradualVerticalTrapezium((*sheet).buffer, sheet, 140, 930, 140 + START_BAR_WIDTH, 930+START_BAR_BG_HEIGHT -5, START_BAR_BG_HEIGHT -5, startColor, endColor, 200);
        drawRectAlpha((*sheet).buffer, sheet, 140, 930+START_BAR_BG_HEIGHT -5, 140+START_BAR_WIDTH, 930+START_BAR_BG_HEIGHT -4, sepColor, 240);
        drawRectAlpha((*sheet).buffer, sheet, 140, 930+START_BAR_BG_HEIGHT -4, 140+START_BAR_WIDTH, 930+START_BAR_BG_HEIGHT , endColor, 200);
    }
}
