
void drawRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color color);

void drawCornerRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color color, Corner corner);

void drawRectAlpha(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color color, int alpha);

void drawGradualVerticalRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor);

void drawGradualVerticalRectAlpha(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor, int alpha);

void drawGradualVerticalTrapezium(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha);

void drawGradualVerticalCornerRect(u8 *buffer, Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor, Corner corner);

void drawCircle(u8 *buffer, Sheet *sheet, int x, int y, int radius, Color color);
