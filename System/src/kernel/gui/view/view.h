/* 
 * The maximum subview number in one view.
 */
#define MAX_SUB_VIEW_NUM 64

typedef struct View View;

typedef struct Sheet Sheet;

typedef struct MouseEvent MouseEvent;

/* 
 * The View data structure represents the View class.It is base class
 * of any displayable view element, and it contains the basic data fields 
 * to display one view and funcions to perform some basic operation on the
 * view.
 */
typedef struct View
{
    Sheet *sheet;

	View *parentView;

	View *subViewList[MAX_SUB_VIEW_NUM];

	u32 subViewNum;

	u32 reference;

	u8 *buffer;

	int x;
	
	int y;

	int z;

	int width;

	int height;

	bool visible;

	/* 
	 * Add the specified view into the container view itself. 
	 *
	 * Parameters:
	 * 		 this: the container view itself.
     *		 view: the subview to be added into the conatiner.
	 * Return:
	 *		the success or failure result
	 */
	bool (*addSubView)(View *this, View *view);

	/* 
	 * Remove the specified view from the container view itself. 
	 *
	 * Parameters:
	 * 		 this: the container view itself.
     *		 view: the subview to be removed from the conatiner.
	 * Return:
	 *		the success or failure result
	 */
	bool (*removeSubView)(View *this, View *view);

	/* 
	 * Set the background of the view itself. 
	 *
	 * Parameters:
	 * 		 this: the view itself.
     *		color: the color that is to be set as the background.
	 * Return:
	 *		the success or failure result.
	 */
	void (*setBackgroundColor)(View *this, Color color);

	/* 
	 * Clear the buffer data of the view itself, i.e make it transparent.
	 *
	 * Parameters:
	 * 		 this: the view itself.
	 * Return:
	 *		no return value.
	 */
	void (*clearView)(View *this);

	/* 
	 * Finally delete the view itself and release all resources on it.
	 *
	 * Parameters:
	 * 		 this: the view itself.
	 * Return:
	 *		no return value.
	 */
	void (*deleteView)(View *this);
	
	/* 
	 * Release and view and its relative memory resources.
	 *
	 * Parameters:
	 * 		 this: the view itself.
	 * Return:
	 *		no return value.
	 */
	void (*releaseView)(View *this);

	/* 
	 * Retain and view and its relative memory resources.
	 *
	 * Parameters:
	 * 		 this: the view itself.
	 * Return:
	 *		no return value.
	 */
	void (*retainView)(View *this);

	/* 
	 * Refresh the rectangle area on view, so that the all subviews
     * content can display and show.
	 *
	 * Parameters:
	 * 		 this: the view itself.
	 * Return:
	 *		no return value.
	 */
	void (*refreshRectView)(View *this);

	/* 
     * The callback funcation of mouse event handler, it is usually 
     * used by the subclass of the view, like button.
	 *
	 * Parameters:
	 * 		 this: the view itself.
     *		event: the mouse event data object.
	 * Return:
	 *		no return value.
	 */
	void (*onMouseDown)(View *this, MouseEvent *event);
	
	/* 
     * The mouse event handler, it is called every time mouse operation
     * is performed.
	 *
	 * Parameters:
	 * 		 this: the view itself.
	 *		event: the mouse event data object.
	 * Return:
	 *		no return value.
	 */
	void (*processMouseDownEvent)(View *this, MouseEvent *event);

} View;

/* 
 * Create and initialize one View object with the specified
 * parameters.
 *
 * Parameters:
 * 		x: the x axis of the view in the parent container.
 *		y: the y axis of the view in the parent container.
 *	width: the width of the view in the parent container.
 * height: the height of the view in the parent container.
 * Return:
 *		View pointer.
 */
View *createView(int x, int y, int width, int height);

/* 
 * Initialize the view object and set the particular functions 
 * to the function pointer variables in the view object.
 *
 * Parameters:
 *	 this: the view object itself.
 * 		x: the x axis of the view in the parent container.
 *		y: the y axis of the view in the parent container.
 *	width: the width of the view in the parent container.
 * height: the height of the view in the parent container.
 * Return:
 *		View pointer.
 */
View *initWithViewFunction(View *this, int x, int y, int width, int height);

/* 
 * Refresh the view rectangle area, so that the subviews in
 * the view object can display and show immediately.
 *
 * Parameters:
 *	 this: the view object itself.
 * 		x: the x axis of the rectangle area in the parent container.
 *		y: the y axis of the rectangle area in the parent container.
 *		w: the width of the rectangle area in the parent container.
 * 		h: the height of the rectangle area in the parent container.
 *		z: the z axis of subviews to be refreshed and shown.
 * Return:
 *		no return value.
 */
void refreshViewRect(View *this, int x, int y, int w, int h, int z);

/* 
 * Fill the view content buffer into its parent sheet buffer.
 *
 * Parameters:
 *	 this: the view object itself.
 * Return:
 *		no return value.
 */
void fillViewToSheetRect(View *this);

