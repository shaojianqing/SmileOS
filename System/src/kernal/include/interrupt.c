void initInterruptHandler()
{
	setInterruptDescriptor(INTERRUPT_TIMING, (int)intHandler20, 2*8, AR_INTGATE32);
}
