
#define FLAGS_OVERRUN			0x0001

/* 
 * The QueueBuffer data structure represents one queue buffer in the OS.
 * The QueueBuffer can be used in the area like mouse input, keyboard input
 * data buffer.
 */
typedef struct QueueBuffer
{
	u32 *buffer;

	int p, q, size, free, flags;
} QueueBuffer;

typedef bool (*Compare)(Object *object1, Object *object2);

/* 
 * Initialize the queue buffer with the specified size and memory buffer.
 *
 * Parameters:
 * 	queueBuffer: the queue buffer to be initialized.
 *		   size: the size of the queue buffer.
 *		 buffer: the memory buffer area of the queue buffer.	
 * Return:
 *		no return value.
 */
void initQueueBuffer(QueueBuffer *queueBuffer, int size, u32 *buffer);

/* 
 * Put the specified data into the queue buffer.
 *
 * Parameters:
 * 	queueBuffer: the queue buffer where to put the data
 *		   data: the data to be put into the queue buffer.
 * Return:
 *		no return value.
 */
int putQueueBuffer(QueueBuffer *queueBuffer, int data);

/* 
 * Get the data at the end of the queue buffer.
 *
 * Parameters:
 * 	queueBuffer: the queue buffer where to get the data
 * Return:
 *		return the data at the end of the queue buffer.
 */
u32 getQueueBuffer(QueueBuffer *queueBuffer);

/* 
 * Get the status of the queue buffer.
 *
 * Parameters:
 * 	queueBuffer: the queue buffer where to get the status
 * Return:
 *		return the status of the queue buffer.
 */
int queueBufferStatus(QueueBuffer *queueBuffer);

/* 
 * Sort the data list with the specified sorting compare function.
 *
 * Parameters:
 * 	     list: the list to be sorted.
 *		 size: the size of the list.
 *	  compare: the sorting compare function.
 * Return:
 *		no return value.
 */
void sort(Object *list[], u32 size, Compare compare);

