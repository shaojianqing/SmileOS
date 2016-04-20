/* 
 * The base address of the sheet table
 * and the map address.
 */
#define SHEET_MANAGE_TABLE 0x29800
#define MAP_ADDRESS 0x100000

/* 
 * The screen size infomation constants. 
 */
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_DENSITY 3

/* 
 * The transparent constants. 
 */
#define TRANSPARENT 0x00

/* 
 * The using status constants of sheet. 
 */
#define STATUS_SHEET_UNUSE 0
#define STATUS_SHEET_USING 1

#define SHEET_NUM 256

typedef struct View View;

typedef struct Image Image;

typedef struct Process Process;

/* 
 * The Sheet data structure represents one window or layer
 * in the screen and is arranged in the z-direction. It contains
 * the data buffer, x and y axis, width and height property, and 
 * other content.
 */
typedef struct Sheet
{
    u8 *buffer;

    int x, y;

	int width, height;

	int z, status;

	bool visible;

	View *contentView;

	Process *process;

} Sheet;

/* 
 * The Sheet Manager data structure manages sheet, maintains
 * sheet list, keeps record of sheetNum and recycles sheet and so on.
 * There is only one instance of Sheet Manager in this OS.
 */
typedef struct SheetManager
{
    u8 sheetNum;

    Sheet *sheets[SHEET_NUM];

    Sheet sheetList[SHEET_NUM];

} SheetManager;

/* 
 * Initialize the SheetManager instance, including building the 
 * initial sheet list, setting default sheet status.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initSheetManagement();

/* 
 * Prepare and return one sheet to the client, meanwhile set the initial
 * value of the sheet.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		sheet pointer.
 */
Sheet* prepareSheet();

/* 
 * Get whether the specified sheet is in the top.
 *
 * Parameters:
 * 		sheet: the sheet to judge whether is in the top.
 * Return:
 *		no return value.
 */
bool isSheetTop(Sheet *sheet);

/* 
 * Set the specified sheet in the top.
 *
 * Parameters:
 * 		sheet: the sheet to be set in the top.
 * Return:
 *		whether it is in the top.
 */
void setSheetTop(Sheet *sheet);

/* 
 * Get the current sheet that covers the specified point (x,y).
 *
 * Parameters:
 * 		x: the x axis of the specified point.
 *		y: the y axis of the specified point.
 * Return:
 *		the current sheet pointer.
 */
Sheet* getCurrentSheet(int x, int y);

/* 
 * Load the view into the sheet and render the view in the sheet.
 *
 * Parameters:
 * 		sheet: the sheet where to load the view.
 *		 view: the view to be loaded into the sheet.
 * Return:
 *		no return value.
 */
void loadContentView(Sheet *sheet, View *view);

/* 
 * Refresh the sheet content in the specified area.
 *
 * Parameters:
 * 		sheet: the sheet to be refreshed.
 *		    x: the x axis of the specified area.
 *			y: the y axis of the specified area.
 *			w: the width of the specified area.
 *			h: the height of the specified area.
 * Return:
 *		no return value.
 */
void refreshSheetRect(Sheet *sheet, int x, int y, int w, int h);

/* 
 * Refresh the specified sheet as well as the other sheets
 * above the specified sheet in the specified area.
 *
 * Parameters:
 * 		sheet: the sheet to be refreshed.
 *		    x: the x axis of the specified area.
 *			y: the y axis of the specified area.
 *			w: the width of the specified area.
 *			h: the height of the specified area.
 * Return:
 *		no return value.
 */
void refreshSheetStack(Sheet *sheet, int x, int y, int w, int h);

/* 
 * Load and refresh the specified sheet, so that the process
 * can render the view in the sheet.
 *
 * Parameters:
 * 		sheet: the sheet to be loaded.
 * Return:
 *		no return value.
 */
void loadWindowSheet(Sheet *sheet);

/* 
 * Slide the sheet to the specified postion(x,y).
 *
 * Parameters:
 * 		sheet: the sheet to be loaded.
 *		    x: the x axis of the position.
 *			y: the y axis of the position.
 * Return:
 *		no return value.
 */
void slideSheet(Sheet *sheet, int x, int y);

/* 
 * Accept the mousedown event and pass it to the contentView,
 * and than the contentView can process the mouse event.
 *
 * Parameters:
 * 		sheet: the sheet to accept the event.
 *		    x: the x axis of the position.
 *			y: the y axis of the position.
 * Return:
 *		no return value.
 */
void processSheetMouseDownEvent(Sheet *sheet, int x, int y);

/* 
 * Show the specified sheet.
 *
 * Parameters:
 * 		sheet: the sheet that will show.
 * Return:
 *		no return value.
 */
void showWindowSheet(Sheet *sheet);

/* 
 * Hide the specified sheet.
 *
 * Parameters:
 * 		sheet: the sheet that will hide.
 * Return:
 *		no return value.
 */
void hideWindowSheet(Sheet *sheet);

/* 
 * Release the specified sheet, so that the SheetManager
 * can recycle it.
 *
 * Parameters:
 * 		sheet: the sheet to be released.
 * Return:
 *		no return value.
 */
void releaseSheet(Sheet *sheet);

/* 
 * Reset the sheet data buffer, so that all data and content
 * will be clear.
 *
 * Parameters:
 * 		sheet: the sheet to be reset.
 * Return:
 *		no return value.
 */
void resetSheet(Sheet *sheet);

