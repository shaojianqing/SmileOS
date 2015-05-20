
typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef struct SegmentDescriptor 
{
	short limitLow, baseLow;

	char baseMid, accessRight;

	char limitHigh, baseHigh;
} SegmentDescriptor;

typedef struct GateDescriptor
{
	short offsetLow, selector;
	
	char dwCount, accessRight;

	short offsetHigh;
} GateDescriptor;

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



