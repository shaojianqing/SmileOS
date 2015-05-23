typedef struct KeyData
{
    int key;
} KeyData;

QueueBuffer keyBuffer;

void intHandler21(int *esp)
{
	outByte(PIC0_OCW2, 0x61);
	u8 data = inByte(PORT_KEYDATA);

	putQueueBuffer(&keyBuffer, data);
	return;
}

void processKeyData(KeyData *keyData, Sheet *input) 
{
	(*keyData).key = getQueueBuffer(&keyBuffer);
	setupInterrupt();
}
