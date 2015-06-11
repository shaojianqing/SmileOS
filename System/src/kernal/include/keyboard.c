typedef struct KeyData
{
    int key;
} KeyData;

void intHandler21()
{
	outByte(PIC0_OCW2, 0x61);
	u8 data = inByte(PORT_KEYDATA);
	putQueueBuffer(&systemBuffer, data+1024);
	return;
}

void processKeyData(KeyData *keyData, u32 data, Sheet *input) 
{
	setupInterrupt();
}
