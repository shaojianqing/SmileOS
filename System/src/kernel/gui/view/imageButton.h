
struct MouseEvent;

typedef struct ImageButton ImageButton;

/* 
 * The ImageButton data structure represents the ImageButton class.
 * It extends the View class, and is used to show one image and perform
 * button operation.
 */
struct ImageButton
{
    View view;

	Image *image;

	Color normalColor;

	Color selectColor;

	/* 
	 * Initialize the imageButton object with specified image data, normalColor 
	 * and selectColor. 
	 *
	 * Parameters:
	 * 		  this: the imageButton object itself.
     *		 image: the image data to render the imageButton.
	 * normalColor: the normalColor of the imageButton.
	 * selectColor: the selectColor of the imageButton.
	 * Return:
	 *		no return value.
	 */
	void (*initWithImage)(ImageButton *this, Image *image, Color normalColor, Color selectColor);
	
	/* 
	 * The callback function of the mouse click operation. 
	 *
	 * Parameters:
	 * 		  this: the imageButton object itself.
     *		 event: the mouse event data object.
	 * Return:
	 *		no return value.
	 */
	void (*onMouseClick)(ImageButton *this, struct MouseEvent *event);

	/* 
	 * Set the appearance of the button to be selected or unselected. 
	 *
	 * Parameters:
	 * 		  this: the imageButton object itself.
     *	  isSelect: the selected or unselected status.
	 * Return:
	 *		no return value.
	 */
	void (*setSelect)(ImageButton *this, bool isSelect);

};

/* 
 * Create and initialize one imageButton object with the specified
 * parameters.
 *
 * Parameters:
 * 		x: the x axis of the imageButton in the parent container.
 *		y: the y axis of the imageButton in the parent container.
 *		w: the width of the imageButton in the parent container.
 *		h: the height of the imageButton in the parent container.
 * Return:
 *		ImageButton pointer.
 */
ImageButton *createImageButton(int x, int y, int w, int h);
