
typedef struct StartButton StartButton;

/* 
 * The StartButton data structure represents the StartButton class.
 * It extends the View class, and is used as the entry button to 
 * start one applicaion.
 */
struct StartButton
{
	/* 
	 * View element at the first place as the parent class of the
     * startButton class.
	 */
    View view;

	/* 
	 * Initialize the startButton object with specified image data. 
	 *
	 * Parameters:
	 * 		 this: the startButton object itself.
     *		image: the image data to render the startButton.
	 * Return:
	 *		no return value.
	 */
	void (*initWithImage)(StartButton *this, Image *image);

};

/* 
 * Create and initialize one StartButton object with the specified
 * parameters.
 *
 * Parameters:
 * 		x: the x axis of the startButton in the parent container.
 *		y: the y axis of the startButton in the parent container.
 *		w: the width of the startButton in the parent container.
 *		h: the height of the startButton in the parent container.
 * sector: the start sector of the icon image data in the harddisk.
 * Return:
 *		StartButton pointer.
 */
StartButton *createStartButton(int x, int y, int w, int h, u32 sector);
