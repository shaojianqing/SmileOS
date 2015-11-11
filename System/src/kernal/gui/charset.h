
#define			CHARSET_DATA_BASE				0x19400


void printChar(View *view, u8 c, int x, int y, Color color);

void printString(View *view, char *string, int size, int x, int y, Color color);

void printInteger(View *view, int value, int x, int y, Color color);

void printHexInteger(View *view, int value, int x, int y, Color color);

void printHexByte(View *view, u8 value, int x, int y, Color color);

void printHexByteTest(u8 *buffer, u8 value, int x, int y, Color color);

void printHexIntegerTest(u8 *buffer, int value, int x, int y, Color color);
