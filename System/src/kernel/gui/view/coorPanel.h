
/* 
 * The origin axis of the center point in the coorPanel.
 */
#define ORIGIN_X				 390
#define ORIGIN_Y		 		 240

typedef struct CoorPanel CoorPanel;

/* 
 * The CoorPanel data structure represents the CoorPanel class.
 * It extends the View class, and is designed to draw a variety
 * of mathmetics pictures.
 */
typedef struct CoorPanel
{
    View view;

	View *canvas;

	/* 
	 * Initialize one coorPanel object with the specified parameters.
	 * 
	 * Parameters:
	 *	  this: the coorPanel object itself.
	 * Return:
	 *		no return value.
	 */
	void (*initPanel)(CoorPanel *this);

	/* 
	 * The draw function pointer variable of the panel with which
     * the panel can draw the particular mathmetics curve.
	 * 
	 * Parameters:
	 *	  this: the coorPanel object itself.
	 * Return:
	 *		no return value.
	 */
	void (*drawFuncation)(CoorPanel *this);

} CoorPanel;

/* 
 * Create and initialize one coorPanel object with the specified
 * parameters.
 *
 * Parameters:
 * 		 x: the x axis of the CoorPanel in the parent container.
 *		 y: the y axis of the CoorPanel in the parent container.
 *		 w: the width of the CoorPanel in the parent container.
 *		 h: the height of the CoorPanel in the parent container.
 * Return:
 *		CoorPanel pointer.
 */
CoorPanel *createCoorPanel(int x, int y, int w, int h);
