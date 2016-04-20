/* 
 * The keyboard key-letter map. This is designed to be the map when performing keyboard
 * operation.
 */
u8 keyTable[0x54];

/* 
 * The x axis of the input letter where next letter will be printed.
 */
int charX;

/* 
 * The KeyData data structure, it represents the keyboard operation. With this data 
 * structure, the kernel can convinently process the keyboard operation and response
 * in the main loop.
 */
typedef struct KeyData
{
    int key;
} KeyData;

/* 
 * Initialize the keyboard data and reset the keyboard status, and then pass the data to the system
 * buffer and process the buffer when keyboard interrupt occurs.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void intHandler21();

/* 
 * Initialize the keyboard table sets, building the map of keyboard key and corresponding letter,
 * so that we can get the letter when performing keyboard operation by checking this map.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initKeyTableSetting();

/* 
 * Process the keyboard data. Firstly fetch the data from the system buffer, and then package the
 * data as the keyboard struct, and then just print the content in the specified sheet letter by letter.
 * With the control of the timer, show and hide the input cursor in turn.
 *
 * Parameters:
 * 		keyData: the keyboard operation data structure generated when keyboard interrupt occurs.
 *		   data: the source data of keyboard interrupt.
 *	      sheet: the input sheet in the screen.
 * Return:
 *		no return value.
 */
void processKeyData(KeyData *keyData, u32 data, Sheet *sheet);

/* 
 * Show the cursor in the specified sheet.
 *
 * Parameters:
 *		sheet: the input sheet in the screen.
 * Return:
 *		no return value.
 */
void showCursor(Sheet *sheet);

/* 
 * Hide the cursor in the specified sheet.
 *
 * Parameters:
 *		sheet: the input sheet in the screen.
 * Return:
 *		no return value.
 */
void hideCursor(Sheet *sheet);
