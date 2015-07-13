
void drawRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color);

void drawCornerRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color, Corner corner);

void drawRectAlpha(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color color, int alpha);

void drawGradualVerticalRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor);

void drawGradualVerticalRectAlpha(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor, int alpha);

void drawGradualVerticalTrapezium(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, int r, Color startColor, Color endColor, int alpha);

void drawGradualVerticalCornerRect(u8 *buffer, Sheet *sheet, int x1, int y1, int x2, int y2, Color startColor, Color endColor, Corner corner);

void drawCircle(u8 *buffer, Sheet *sheet, int x0, int y0, int radius, Color color);
