/* 
 * The base address of the GDT and IDT table.
 */
#define ADDRESS_GDT 0x07e00
#define ADDRESS_IDT 0x17e00

/* 
 * The limit of the IDT table.
 */
#define LIMIT_IDT 0x7FF

/* 
 * The GlobalDescriptor data structure that represents the GDT data item.
 */
typedef struct GlobalDescriptor 
{
	short limitLow, baseLow;

	char baseMid, accessRight;

	char limitHigh, baseHigh;

} GlobalDescriptor;

/* 
 * The LocalDescriptor data structure that represents the LDT data item.
 */
typedef struct LocalDescriptor 
{
	short limitLow, baseLow;

	char baseMid, accessRight;

	char limitHigh, baseHigh;

} LocalDescriptor;

/* 
 * The GateDescriptor data structure that represents the Gate Descriptor data item.
 */
typedef struct GateDescriptor
{
	short offsetLow, selector;
	
	char dwCount, accessRight;

	short offsetHigh;

} GateDescriptor;

/* 
 * Load the base and limit of GDT table into the GDTR register.
 *
 * Parameters:
 * 		limit: the limit of the GDT table.
 *		 addr: the base address of the GDT table.
 * Return:
 *		no return value.
 */
void loadGdtr(int limit, int addr);

/* 
 * Load the base and limit of IDT table into the IDTR register.
 *
 * Parameters:
 * 		limit: the limit of the IDT table.
 *		 addr: the base address of the IDT table.
 * Return:
 *		no return value.
 */
void loadIdtr(int limit, int addr);

/* 
 * Build and set the particiular GDT item into the GDT table.
 *
 * Parameters:
 * descNumber: the number of the GDT table.
 * 		limit: the limit of the GDT table.
 *		 base: the base address of the GDT table.
 *		   ar: the attributes of the GDT item.
 * Return:
 *		no return value.
 */
void setGlobalDescriptor(int descNumber, u32 limit, int base, int ar);

/* 
 * Build and set the particiular IDT item into the IDT table.
 *
 * Parameters:
 *  intNumber: the number of the IDT table.
 * 	   offset: the segment offset to the GDT entry point.
 *   selector: the GDT selector of the entry point.
 *		   ar: the attributes of the IDT item.
 * Return:
 *		no return value.
 */
void setInterruptDescriptor(int intNumber, int offset, int selector, int ar);

/* 
 * Build and set the particiular LDT item into the LDT table.
 *
 * Parameters:
 *	  address: the base address of the LDT table
 * descNumber: the number of the LDT table.
 * 		limit: the limit of the LDT table.
 *		 base: the base address of the LDT table.
 *		   ar: the attributes of the LDT item.
 * Return:
 *		no return value.
 */
void setLocalDescriptor(int address, int descNumber, u32 limit, int base, int ar);

/* 
 * Build and set the particiular Call Gate Descriptor item into the GDT table.
 *
 * Parameters:
 *  intNumber: the number of the IDT table.
 * 	   offset: the segment offset to the GDT entry point.
 *   selector: the GDT selector of the entry point.
 *		count: the count of parameters when being called.
 *		   ar: the attributes of the call gate item.
 * Return:
 *		no return value.
 */
void setCallGateDescriptor(int intNumber, int offset, int selector, int count, int ar);
