
/* 
 * The base address and the limit of the IDT table.
 */
#define ADDRESS_IDT 		0x17e00
#define LIMIT_IDT 			0x7FF

/* 
 * The Attributes of interrupt gate descriptor.
 */
#define AR_INTGATE32 		0x008e

/* 
 * The system hardware interrupts number in the OS.
 */
#define INTERRUPT_MOUSE 	0x2c
#define INTERRUPT_TIMING 	0x20
#define INTERRUPT_KEYBOARD	0x21
#define INTERRUPT_HARDDISK 	0x2e

/* 
 * The C function signature of the assembly procedure. It is called when timing
 * interrupt occurs.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void asmIntHandler20();

/* 
 * The C function signature of the assembly procedure. It is called when keyboard
 * interrupt occurs.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void asmIntHandler21();

/* 
 * The C function signature of the assembly procedure. It is called when mouse
 * interrupt occurs.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void asmIntHandler2c();

/* 
 * The C function signature of the assembly procedure. It is called when harddisk
 * interrupt occurs.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void asmIntHandler2e();

/* 
 * Initialize, registe the interrupt handler to the IDT table and load the IDT
 * table into the IDTR register.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initInterruptHandler();
