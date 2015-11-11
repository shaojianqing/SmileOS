
#define FLAGS_OVERRUN			0x0001

typedef struct QueueBuffer
{
	u32 *buffer;

	int p, q, size, free, flags;
} QueueBuffer;

typedef bool (*Compare)(Object *object1, Object *object2);

void initQueueBuffer(QueueBuffer *queueBuffer, int size, u32 *buffer);

int putQueueBuffer(QueueBuffer *queueBuffer, int data);

u32 getQueueBuffer(QueueBuffer *queueBuffer);

int queueBufferStatus(QueueBuffer *queueBuffer);

void sort(Object *list[], u32 num, Compare compare);

