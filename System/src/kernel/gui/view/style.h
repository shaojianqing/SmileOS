/* 
 * The Button Style data structure represents one kind of style
 * when rendering one button, it contains some appearnce features
 * of the button, including borderColor, startColor, endColor,
 * startDownColor, endDownColor, textColor, shadowColor and corner. 
 */
typedef struct ButtonStyle
{
	Color borderColor;
 
	Color startColor; 
	
	Color endColor;

	Color startDownColor; 

	Color endDownColor;

	Color textColor; 

	Color shadowColor;

	Corner corner;

} ButtonStyle;

/* 
 * Prepare and set the DarkRed color style, and than
 * return the color style.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		ButtonStyle pointer.
 */
ButtonStyle* ButtonStyleDarkRed();

/* 
 * Prepare and set the LightGray color style, and than
 * return the color style.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		ButtonStyle pointer.
 */
ButtonStyle* ButtonStyleLightGray();

/* 
 * Prepare and set the LightBlue color style, and than
 * return the color style.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		ButtonStyle pointer.
 */
ButtonStyle* ButtonStyleLightBlue();

/* 
 * Prepare and set the DarkBlue color style, and than
 * return the color style.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		ButtonStyle pointer.
 */
ButtonStyle* ButtonStyleDarkBlue();

/* 
 * Prepare and set the DarkOrange color style, and than
 * return the color style.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		ButtonStyle pointer.
 */
ButtonStyle* ButtonStyleDarkOrange();

/* 
 * Prepare and set the BlackBlue color style, and than
 * return the color style.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		ButtonStyle pointer.
 */
ButtonStyle* ButtonStyleBlackBlue();
