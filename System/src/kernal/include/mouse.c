QueueBuffer mouseBuffer;

void intHandler2c(int *esp)
{
	u8 data;
	outByte(PIC1_OCW2, 0x64);
	outByte(PIC0_OCW2, 0x62);
	data = inByte(PORT_KEYDATA);
	putQueueBuffer(&mouseBuffer, data);
	return;
}
