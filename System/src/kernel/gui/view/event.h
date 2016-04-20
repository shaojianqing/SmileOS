
/* 
 * The MouseEvent data structure represents one mouse operation
 * data in this OS. It contains x and y offset, as well as the 
 * btn which represents the operation type on the mouse. It is
 * designed as the parameter passed to the target like button, 
 * imageButton.
 */
typedef struct MouseEvent 
{
	int x;
	
	int y;

	int btn;

} MouseEvent;
