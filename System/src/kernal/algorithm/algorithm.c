#include "../const/const.h"
#include "../type/type.h"
#include "../gui/sheet.h"
#include "../execute/execute.h"
#include "../system/descriptor.h"
#include "../process/process.h"
#include "algorithm.h"

extern Process *kernelProcess;

void initQueueBuffer(QueueBuffer *queueBuffer, int size, u32 *buffer)
{
	(*queueBuffer).size = size;
	(*queueBuffer).buffer = buffer;
	(*queueBuffer).free = size;
	(*queueBuffer).flags = 0;
	(*queueBuffer).p = 0;
	(*queueBuffer).q = 0;
	return;
}

int putQueueBuffer(QueueBuffer *queueBuffer, int data)
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

u32 getQueueBuffer(QueueBuffer *queueBuffer)
{
	u32 data;
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

void sort(Object *list[], u32 num, Compare compare)
{
	if (num>1) {
		Object *minObject;
		u32 i=0, j=0, index=0;
		for (i=0;i<num-1;++i) {
			minObject = list[i];
			for (j=i+1;j<num;++j) {
				Object *object = list[j];
				if (compare(minObject, object)==TRUE) {
					minObject = object;
					index = j;
				}							
			}
			if (minObject!=list[i]) {
				Object *object = list[i];
				list[index] = object;
				list[i] = minObject;
			}			
		}
	}
}

