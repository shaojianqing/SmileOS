#include "../const/const.h"
#include "../type/type.h"
#include "../algorithm/algorithm.h"
#include "peripheral.h"

extern int systemDataBuffer[1024];

extern QueueBuffer systemBuffer;

void waitKBCReady()
{
	while (TRUE) {
		if ((inByte(PORT_KEYSTAT) & KEYSTA_SEND_NOTREADY) == 0) {
			break;
		}
	}
	return;
}

void initTiming()
{
	outByte(PIT_CTRL, 0x34);
	outByte(PIT_CNT0, 0x9c);
	outByte(PIT_CNT0, 0x2e);
	return;
}

void initKeyboard()
{
	waitKBCReady();
	outByte(PORT_KEYCMD, KEYCMD_WRITE_MODE);
	waitKBCReady();
	outByte(PORT_KEYDATA, KBC_MODE);
	return;
}

void initMouseData()
{
	waitKBCReady();
	outByte(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
	waitKBCReady();
	outByte(PORT_KEYDATA, MOUSECMD_ENABLE);
	return;
}

void initPeripheralStatus()
{
	initTiming();
	initKeyboard();
	initMouseData();
}

void initQueueBufferData()
{
	initQueueBuffer(&systemBuffer, SYSTEM_BUFFER_SIZE, systemDataBuffer);
}

