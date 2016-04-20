/* 
 * The height of the top info bar.
 */
#define INFO_BAR_HEIGHT 24

/* 
 * The height of the bottom start bar background.
 */
#define START_BAR_BG_HEIGHT 80

/* 
 * The width and height of the bottom start.
 */
#define START_BAR_WIDTH 800
#define START_BAR_HEIGHT 120

/* 
 * Initialize the desktop info sheet, including the initialization
 * of the background sheet, info bar sheet, start bar sheet, mouse
 * sheet, and finally render and refresh them.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initDesktopInfoSheet();

/* 
 * Rearrange the desktop info sheet when new sheet is added into the
 * desktop sheet list or one sheet is removed from the desktop sheet
 * list.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void reArrangeDesktopSheet();

/* 
 * Set the desktop background image with the specified background color.
 *
 * Parameters:
 * 		bgCode: the background image code.
 * Return:
 *		no return value.
 */
void setBackground(u32 bgCode);
