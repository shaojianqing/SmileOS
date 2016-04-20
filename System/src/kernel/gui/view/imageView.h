
typedef struct ImageView ImageView;

/* 
 * The ImageView data structure represents the ImageView class.
 * It extends the View class, and is used to show one image in 
 * the particular view area.
 */
typedef struct ImageView
{
    View view;

	Image *image;

	/* 
	 * Initialize the imageView object with specified image data and borderColor. 
	 *
	 * Parameters:
	 * 		  this: the startButton object itself.
     *		 image: the image data to render the startButton.
	 * borderColor: the borderColor of the imageView.
	 * Return:
	 *		no return value.
	 */
	void (*initWithImage)(ImageView *this, Image *image, Color borderColor);

} ImageView;

/* 
 * Create and initialize one imageView object with the specified
 * parameters.
 *
 * Parameters:
 * 		x: the x axis of the imageView in the parent container.
 *		y: the y axis of the imageView in the parent container.
 *		w: the width of the imageView in the parent container.
 *		h: the height of the imageView in the parent container.
 * Return:
 *		ImageView pointer.
 */
ImageView *createImageView(int x, int y, int w, int h);
