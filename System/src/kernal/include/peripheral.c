char keyDataBuffer[KEY_BUFFER_SIZE], mouseDataBuffer[MOUSE_BUFFER_SIZE];

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
	initQueueBuffer(&keyBuffer, KEY_BUFFER_SIZE, keyDataBuffer);
	initQueueBuffer(&mouseBuffer, MOUSE_BUFFER_SIZE, mouseDataBuffer);
}

