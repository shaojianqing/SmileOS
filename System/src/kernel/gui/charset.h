/* 
 * The base address of the charset library.
 */
#define			CHARSET_DATA_BASE				0x19400

/* 
 * The width and height of one character in the charset library.
 */
#define			CHARSET_WIDTH					0x08
#define			CHARSET_HEIGHT					0x10

/* 
 * Print the character in the view at the particular position with the specified color.
 *
 * Parameters:
 * 		  view: the view where to print the character.
 *		     c: the character to be printed.
 *		     x: the x axis of the character to be printed.
 *		     y: the y axis of the character to be printed.
 *   mainColor: the main color of the character to be printed.	
 * shadowColor: the shadow color of the character to be printed.	
 * Return:
 *		no return value.
 */
void printChar(View *view, u8 c, int x, int y, Color mainColor, Color shadowColor);

/* 
 * Print the string in the view at the particular position with the specified color.
 *
 * Parameters:
 * 		  view: the view where to print the string.
 *		string: the string to be printed.
 *		  size: the size of the string to be printed.
 *		     x: the start x axis of the string to be printed.
 *		     y: the start y axis of the string to be printed.
 *   mainColor: the main color of the string to be printed.	
 * shadowColor: the shadow color of the string to be printed.	
 * Return:
 *		no return value.
 */
void printString(View *view, char *string, int size, int x, int y, Color mainColor, Color shadowColor);

/* 
 * Print the integer in the view at the particular position with the specified color.
 *
 * Parameters:
 * 		  view: the view where to print the integer.
 *		 value: the integer to be printed.
 *		     x: the start x axis of the integer to be printed.
 *		     y: the start y axis of the integer to be printed.
 *   mainColor: the main color of the integer to be printed.	
 * shadowColor: the shadow color of the integer to be printed.	
 * Return:
 *		no return value.
 */
void printInteger(View *view, int value, int x, int y, Color mainColor, Color shadowColor);

/* 
 * Print the integer in the view at the particular position with the specified color and in the 
 * hex format.
 *
 * Parameters:
 * 		  view: the view where to print the integer.
 *		 value: the integer to be printed.
 *		     x: the start x axis of the integer to be printed.
 *		     y: the start y axis of the integer to be printed.
 *   mainColor: the main color of the integer to be printed.	
 * shadowColor: the shadow color of the integer to be printed.	
 * Return:
 *		no return value.
 */
void printHexInteger(View *view, int value, int x, int y, Color mainColor, Color shadowColor);

/* 
 * Print the byte in the view at the particular position with the specified color and in the 
 * hex format.
 *
 * Parameters:
 * 		  view: the view where to print the byte.
 *		 value: the byte to be printed.
 *		     x: the start x axis of the byte to be printed.
 *		     y: the start y axis of the byte to be printed.
 *   mainColor: the main color of the byte to be printed.	
 * shadowColor: the shadow color of the byte to be printed.	
 * Return:
 *		no return value.
 */
void printHexByte(View *view, u8 value, int x, int y, Color mainColor, Color shadowColor);
