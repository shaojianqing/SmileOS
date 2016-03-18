#include "../const/const.h"

/* 
 * The System buffer storage to store data from mouse or key interrupts, and be fetched by the 
 * main event loop in the kernel.
 */
int systemDataBuffer[SYSTEM_BUFFER_SIZE];

/* 
 * The System buffer to buffer data from mouse or key interrupts, and be fetched by the 
 * main event loop in the kernel.
 */
QueueBuffer systemBuffer;
