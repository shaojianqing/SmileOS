#define MOUSE_WIDTH 			12
#define MOUSE_HEIGHT			22

#define MOUSE_DOWN_EVENT		0x01

/* 
 * The MouseData data structure, it represents one mouse operation data and contains 
 * the mouse offset, status and operation when mouse interrupt occurs.With this data  
 * structure, the kernel can convinently process the mouse operation and response in 
 * the screen fluently in the main loop.
 */
typedef struct MouseData
{
    signed char buf[3];

    u8 phase;

    int x, y;

    int btn;
} MouseData;

/* 
 * Initialize the mouse data and reset the mouse status, and then pass the data to the system
 * buffer and process the buffer when mouse interrupt occurs.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void intHandler2c();

/* 
 * Process the mouse data. Firstly fetch the data from the system buffer, and then package the
 * data as the MouseData struct, and then perform some operation according to the phase field,
 * finally redraw the mouse cursor in the screen or trigger the events as the response to user.
 *
 * Parameters:
 * 		mouseData: the mouse operation data structure generated when mouse interrupt occurs.
 *		     data: the source data of mouse interrupt.
 *			mouse: the mouse sheet in the screen that is to be redrawn in the most cases.
			   mx: the previous mouse cursor x axis in the screen.
			   my: the previout mouse cursor y axis in the screen.
 * Return:
 *		no return value.
 */
void processMouseData(MouseData *mouseData, u32 data, Sheet *mouse, int *mx, int *my);
