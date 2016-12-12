
struct Factory;

struct ButtonStyle;

typedef struct Button Button;

/* 
 * The Button data structure represents the Button class.
 * It extends the View class, and is designed to be the
 * button object. 
 */
struct Button
{
    View view;

	bool select;

	char *title;

	int length;

	Image *image;

	struct Factory *factory;

	struct ButtonStyle* (*buttonStyleType)();

	/* 
	 * Initialize one button object with the specified parameters.
	 * 
	 * Parameters:
	 *	  this: the button object itself.
	 *    text: the title shown in the button.
	 *  length: the lenth of the title.
	 * buttonStyleType: the style type function pointer of the button.
	 * Return:
	 *		no return value.
	 */
	void (*initButton)(Button *this, char *text, int length, struct ButtonStyle* (*buttonStyleType)());

	/* 
	 * The callback function of the mouse click operation.
	 *
	 * Parameters:
	 * 		  this: the button object itself.
     *		 event: the mouse event data object.
	 * Return:
	 *		no return value.
	 */
	void (*onMouseClick)(Button *this, MouseEvent *event);

	/* 
	 * Set the appearance of the button to be selected or unselected. 
	 *
	 * Parameters:
	 * 		  this: the button object itself.
     *	  isSelect: the selected or unselected status.
	 * Return:
	 *		no return value.
	 */
	void (*selectButton)(Button *this, bool select);

	/* 
	 * The callback function of timing event, it is called 
     * when time signal from the factory goes to end.
	 *
	 * Parameters:
     *		no parameters.
	 * Return:
	 *		no return value.
	 */
	void (*buttonOnTimer)();

};

/* 
 * Create and initialize one button object with the specified
 * parameters.
 *
 * Parameters:
 * 		 x: the x axis of the imageButton in the parent container.
 *		 y: the y axis of the imageButton in the parent container.
 *		 w: the width of the imageButton in the parent container.
 *		 h: the height of the imageButton in the parent container.
 * factory: the button status factory that is used to control the status.
 *   image: the button icon image to be shown somewhere in the button.
 * Return:
 *		Button pointer.
 */
Button *createButton(int x, int y, int w, int h, struct Factory *factory, Image *image);
