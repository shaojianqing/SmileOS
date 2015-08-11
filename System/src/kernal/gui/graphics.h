
#define LINE_THIN 1
#define LINE_BOLD 2

#define DIRECTION_UP 1
#define DIRECTION_DOWN 2


void drawLine(View *view, int x1, int y1, int x2, int y2, Color color, int style);

void drawImage(View *view, int x, int y, Image *image);

void drawRect(View *view, int x, int y, int w, int h, Color color);

void drawCornerRect(View *view, int x, int y, int w, int h, Color color, Corner corner);

void drawRectAlpha(View *view, int x, int y, int w, int h, Color color, int alpha);

void drawGradualVerticalRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor);

void drawGradualVerticalRectAlpha(View *view, int x, int y, int w, int h, Color startColor, Color endColor, int alpha);

void drawGradualVerticalTrapezium(View *view, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha);

void drawGradualVerticalCornerRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor, Corner corner, int direction);

void drawCircle(View *view, int x, int y, int radius, Color color);

void drawGradualVerticalRectAlphaInSheet(Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor, int alpha);

void drawGradualVerticalTrapeziumInSheet(Sheet *sheet, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha);

void drawRectAlphaInSheet(Sheet *sheet, int x, int y, int w, int h, Color color, int alpha);
