typedef unsigned char bool;

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef unsigned long u64;

typedef struct QueueBuffer
{
	u32 *buffer;

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



