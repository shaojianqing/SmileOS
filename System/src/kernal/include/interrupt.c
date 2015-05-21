void asmIntHandler21();

void asmIntHandler2c();

void initInterruptHandler()
{
	setInterruptDescriptor(INTERRUPT_KEYBOARD, (int)asmIntHandler2c, 8, AR_INTGATE32);
	setInterruptDescriptor(INTERRUPT_MOUSE, (int)asmIntHandler2c, 8, AR_INTGATE32);
	loadIdtr(LIMIT_IDT, ADDRESS_IDT);	
}
