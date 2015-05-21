char keyDataBuffer[1024], mouseDataBuffer[1024];

void waitKBCReady()
{
	while (TRUE) {
		if ((inByte(PORT_KEYSTAT) & KEYSTA_SEND_NOTREADY) == 0) {
			break;
		}
	}
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
	initKeyboard();
	initMouseData();
}

void initQueueBufferData()
{
	initQueueBuffer(&keyBuffer, 1024, keyDataBuffer);
	initQueueBuffer(&mouseBuffer, 1024, mouseDataBuffer);
}

