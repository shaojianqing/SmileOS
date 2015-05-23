void initQueueBuffer(QueueBuffer *queueBuffer, int size, u8 *buffer)
{
	(*queueBuffer).size = size;
	(*queueBuffer).buffer = buffer;
	(*queueBuffer).free = size;
	(*queueBuffer).flags = 0;
	(*queueBuffer).p = 0;
	(*queueBuffer).q = 0;
	return;
}

int putQueueBuffer(QueueBuffer *queueBuffer, signed char data)
{
	if ((*queueBuffer).free == 0) {
		(*queueBuffer).flags |= FLAGS_OVERRUN;
		return -1;
	}
	(*queueBuffer).buffer[(*queueBuffer).p] = data;
	(*queueBuffer).p++;
	if ((*queueBuffer).p == (*queueBuffer).size) {
		(*queueBuffer).p = 0;
	}
	(*queueBuffer).free--;
	return 0;
}

u8 getQueueBuffer(QueueBuffer *queueBuffer)
{
	u8 data;
	if ((*queueBuffer).free == (*queueBuffer).size) {
		return -1;
	}
	data = (*queueBuffer).buffer[(*queueBuffer).q];
	(*queueBuffer).q++;
	if ((*queueBuffer).q == (*queueBuffer).size) {
		(*queueBuffer).q = 0;
	}
	(*queueBuffer).free++;
	return data;
}

int queueBufferStatus(QueueBuffer *queueBuffer)
{
	return (*queueBuffer).size - (*queueBuffer).free;
}
