
/* 
 * The origin axis of the start point in the graphPanel.
 */
#define ORIGIN_X			10
#define ORIGIN_Y			10

typedef struct GraphPanel GraphPanel;

/* 
 * The GraphPanel data structure represents the GraphPanel class.
 * It extends the View class, and is designed to draw a variety
 * of statistics graph like bar graph, line graph.
 */
typedef struct GraphPanel
{
    View view;

	View *canvas;

	/* 
	 * Initialize one graphPanel object with the specified parameters.
	 * 
	 * Parameters:
	 *	  this: the graphPanel object itself.
	 * Return:
	 *		no return value.
	 */
	void (*initPanel)(GraphPanel *this);

	/* 
	 * The draw function pointer variable of the panel with which
     * the panel can draw the particular statistics graph.
	 * 
	 * Parameters:
	 *	  this: the graphPanel object itself.
	 * Return:
	 *		no return value.
	 */
	void (*drawGraph)(GraphPanel *this);

} GraphPanel;

/* 
 * Create and initialize one graphPanel object with the specified
 * parameters.
 *
 * Parameters:
 * 		 x: the x axis of the graphPanel in the parent container.
 *		 y: the y axis of the graphPanel in the parent container.
 *		 w: the width of the graphPanel in the parent container.
 *		 h: the height of the graphPanel in the parent container.
 * Return:
 *		GraphPanel pointer.
 */
GraphPanel *createGraphPanel(int x, int y, int w, int h);
