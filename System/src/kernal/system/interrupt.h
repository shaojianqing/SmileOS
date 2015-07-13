
#define ADDRESS_IDT 		0x17e00
#define LIMIT_IDT 			0x7FF

#define AR_INTGATE32 		0x008e

#define INTERRUPT_MOUSE 	0x2c
#define INTERRUPT_TIMING 	0x20
#define INTERRUPT_KEYBOARD	0x21
#define INTERRUPT_HARDDISK 	0x2e

void asmIntHandler20();

void asmIntHandler21();

void asmIntHandler2c();

void asmIntHandler2e();

void initInterruptHandler();
