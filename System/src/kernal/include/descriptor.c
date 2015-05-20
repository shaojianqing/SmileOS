void setInterruptDescriptor(int intNumber, int offset, int selector, int ar) 
{
	GateDescriptor *idtBase = (GateDescriptor *)ADDRESS_IDT;
	(*(idtBase+intNumber)).offsetLow = offset & 0xFFFF;
	(*(idtBase+intNumber)).selector = selector;
	(*(idtBase+intNumber)).dwCount = (ar>>8) & 0xFF;
	(*(idtBase+intNumber)).accessRight = ar & 0xFF;
	(*(idtBase+intNumber)).offsetHigh = (offset>>16) & 0xFFFF;
}
