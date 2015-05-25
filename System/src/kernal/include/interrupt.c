void asmIntHandler20();

void asmIntHandler21();

void asmIntHandler2c();

void asmIntHandler2e();

void initInterruptHandler()
{
	setInterruptDescriptor(INTERRUPT_TIMING, (int)asmIntHandler20, 8, AR_INTGATE32);
	setInterruptDescriptor(INTERRUPT_KEYBOARD, (int)asmIntHandler21, 8, AR_INTGATE32);
	setInterruptDescriptor(INTERRUPT_MOUSE, (int)asmIntHandler2c, 8, AR_INTGATE32);
	setInterruptDescriptor(INTERRUPT_HARDDISK, (int)asmIntHandler2e, 8, AR_INTGATE32);
	loadIdtr(LIMIT_IDT, ADDRESS_IDT);	
}
