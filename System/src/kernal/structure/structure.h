
typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef unsigned long u64;

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

typedef struct QueueBuffer
{
	u8 *buffer;

	int p, q, size, free, flags;
} QueueBuffer;

typedef struct Color
{
    u8 red;

    u8 green;

    u8 blue;
} Color;

typedef struct Corner
{
    u32 leftTop;

    u32 rightTop;

    u32 leftBtm;

    u32 rightBtm;
} Corner;



