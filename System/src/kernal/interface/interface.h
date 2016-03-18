#define AR_386CGate 0x8c

/* 
 * Initialize and registe system call interface, now the form of the interface is 
 * exactly the i386 call gate.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initInterfaceTable();
