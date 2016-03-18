/* 
 * The line style constants: thin and bold lines.
 */
#define LINE_THIN 1
#define LINE_BOLD 2

#define DIRECTION_UP 1
#define DIRECTION_DOWN 2

/* 
 * Draw the background of the specified sheet with the image data.
 *
 * Parameters:
 * 		sheet: the sheet where to draw the background.
 *		image: the image data as the background source.
 * Return:
 *		no return value.
 */
void drawBackround(Sheet *sheet, Image *image);

/* 
 * Draw one point in the view with the specified color.
 *
 * Parameters:
 * 		view: the view where to draw the point.
 *		   x: the x axis of the point.
 *		   y: the y axis of the point.
 *	   color: the color of the point.
 * Return:
 *		no return value.
 */
void drawPoint(View *view, int x, int y, Color color);

/* 
 * Draw one bold point in the view with the specified color.
 *
 * Parameters:
 * 		view: the view where to draw the point.
 *		   x: the x axis of the point.
 *		   y: the y axis of the point.
 *	   color: the color of the point.
 * Return:
 *		no return value.
 */
void drawBoldPoint(View *view, int x, int y, Color color);

/* 
 * Draw one line in the view with the specified color and style.
 *
 * Parameters:
 * 		view: the view where to draw the line.
 *		  x1: the start x axis of the line.
 *		  y1: the start y axis of the line.
 *	      x2: the end x axis of the line.
 *		  y2: the end y axis of the line.
 *	   color: the color of the line.
 *	   style: the style of the line (thin or bold).
 * Return:
 *		no return value.
 */
void drawLine(View *view, int x1, int y1, int x2, int y2, Color color, int style);

/* 
 * Draw one image in the view at the specified position.
 *
 * Parameters:
 * 		view: the view where to draw the image.
 *		   x: the left-top x axis of the image in the view.
 *		   y: the left-top y axis of the image in the view.
 *	   image: the image data to be drawn in the view.
 * Return:
 *		no return value.
 */
void drawImage(View *view, int x, int y, Image *image);

/* 
 * Draw one rectangle in the view with specified color.
 *
 * Parameters:
 * 		view: the view where to draw the rectangle.
 *		   x: the left-top x axis of the rectangle in the view.
 *		   y: the left-top y axis of the rectangle in the view.
 *		   w: the width of the rectangle in the view.
 *		   h: the height of the rectangle in the view.
 *	   color: the filling color of the rectangle in the view.
 * Return:
 *		no return value.
 */
void drawRect(View *view, int x, int y, int w, int h, Color color);

/* 
 * Draw one cornered rectangle in the view with specified color.
 *
 * Parameters:
 * 		view: the view where to draw the rectangle.
 *		   x: the left-top x axis of the rectangle in the view.
 *		   y: the left-top y axis of the rectangle in the view.
 *		   w: the width of the rectangle in the view.
 *		   h: the height of the rectangle in the view.
 *	   color: the filling color of the rectangle in the view.
 *    corner: the corner data of the rectangle in the view.
 * Return:
 *		no return value.
 */
void drawCornerRect(View *view, int x, int y, int w, int h, Color color, Corner corner);

/* 
 * Draw one rectangle in the view with alpha transparent.
 *
 * Parameters:
 * 		view: the view where to draw the rectangle.
 *		   x: the left-top x axis of the rectangle in the view.
 *		   y: the left-top y axis of the rectangle in the view.
 *		   w: the width of the rectangle in the view.
 *		   h: the height of the rectangle in the view.
 *	   color: the filling color of the rectangle in the view.
 *     alpha: the transparent degree of the rectangle in the view.
 * Return:
 *		no return value.
 */
void drawRectAlpha(View *view, int x, int y, int w, int h, Color color, int alpha);

/* 
 * Draw one rectangle in the view with gradual color changes in vertical direction.
 *
 * Parameters:
 * 		view: the view where to draw the rectangle.
 *		   x: the left-top x axis of the rectangle in the view.
 *		   y: the left-top y axis of the rectangle in the view.
 *		   w: the width of the rectangle in the view.
 *		   h: the height of the rectangle in the view.
 *startColor: the gradual startColor of the rectangle in the view.
 *  endColor: the gradual endColor of the rectangle in the view.
 * Return:
 *		no return value.
 */
void drawGradualVerticalRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor);

/* 
 * Draw one rectangle in the view with gradual color changes in vertical direction and alpha transparent.
 *
 * Parameters:
 * 		view: the view where to draw the rectangle.
 *		   x: the left-top x axis of the rectangle in the view.
 *		   y: the left-top y axis of the rectangle in the view.
 *		   w: the width of the rectangle in the view.
 *		   h: the height of the rectangle in the view.
 *startColor: the gradual startColor of the rectangle in the view.
 *  endColor: the gradual endColor of the rectangle in the view.
 *	   alpha: the transparent degree of the rectangle in the view.
 * Return:
 *		no return value.
 */
void drawGradualVerticalRectAlpha(View *view, int x, int y, int w, int h, Color startColor, Color endColor, int alpha);

/* 
 * Draw one trapezium in the view with gradual color changes in vertical direction and alpha transparent.
 *
 * Parameters:
 * 		view: the view where to draw the trapezium.
 *		   x: the left-top x axis of the trapezium in the view.
 *		   y: the left-top y axis of the trapezium in the view.
 *		   w: the width of the trapezium in the view.
 *		   h: the height of the trapezium in the view.
 *		   r: the angle of the trapezium in the view.
 *startColor: the gradual startColor of the trapezium in the view.
 *  endColor: the gradual endColor of the trapezium in the view.
 *	   alpha: the transparent degree of the trapezium in the view.
 * Return:
 *		no return value.
 */
void drawGradualVerticalTrapezium(View *view, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha);

void drawGradualVerticalCornerRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor, Corner corner, int direction);

void drawGradualHorizontalCornerRect(View *view, int x, int y, int w, int h, Color startColor, Color endColor, Corner corner, int direction);

/* 
 * Draw one circle in the view with specified color.
 *
 * Parameters:
 * 		view: the view where to draw the circle.
 *		   x: the x axis of the circle center in the view.
 *		   y: the y axis of the circle center in the view.
 *	  radius: the radius of the circle center in the view.
 *     color: the filling color of the circle in the view.
 * Return:
 *		no return value.
 */
void drawCircle(View *view, int x, int y, int radius, Color color);

void drawGradualVerticalRectAlphaInSheet(Sheet *sheet, int x, int y, int w, int h, Color startColor, Color endColor, int alpha);

void drawGradualVerticalTrapeziumInSheet(Sheet *sheet, int x, int y, int w, int h, int r, Color startColor, Color endColor, int alpha);

/* 
 * Draw one rectangle in the sheet with alpha transparent.
 *
 * Parameters:
 * 	   sheet: the sheet where to draw the rectangle.
 *		   x: the left-top x axis of the rectangle in the sheet.
 *		   y: the left-top y axis of the rectangle in the sheet.
 *		   w: the width of the rectangle in the sheet.
 *		   h: the height of the rectangle in the sheet.
 *	   color: the filling color of the rectangle in the sheet.
 *     alpha: the transparent degree of the rectangle in the sheet.
 * Return:
 *		no return value.
 */
void drawRectAlphaInSheet(Sheet *sheet, int x, int y, int w, int h, Color color, int alpha);
