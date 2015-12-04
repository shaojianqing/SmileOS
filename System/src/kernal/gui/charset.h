
#define			CHARSET_DATA_BASE				0x19400

#define			CHARSET_WIDTH					0x08
#define			CHARSET_HEIGHT					0x10

void printChar(View *view, u8 c, int x, int y, Color mainColor, Color shadowColor);

void printString(View *view, char *string, int size, int x, int y, Color mainColor, Color shadowColor);

void printInteger(View *view, int value, int x, int y, Color mainColor, Color shadowColor);

void printHexInteger(View *view, int value, int x, int y, Color mainColor, Color shadowColor);

void printHexByte(View *view, u8 value, int x, int y, Color mainColor, Color shadowColor);
