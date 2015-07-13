#define ADDRESS_GDT 0x07e00
#define ADDRESS_IDT 0x17e00
#define LIMIT_IDT 0x7FF

typedef struct GlobalDescriptor 
{
	short limitLow, baseLow;

	char baseMid, accessRight;

	char limitHigh, baseHigh;
} GlobalDescriptor;

typedef struct GateDescriptor
{
	short offsetLow, selector;
	
	char dwCount, accessRight;

	short offsetHigh;
} GateDescriptor;

void loadGdtr(int limit, int addr);

void loadIdtr(int limit, int addr);

void setGlobalDescriptor(int descNumber, u32 limit, int base, int ar);

void setInterruptDescriptor(int intNumber, int offset, int selector, int ar);
