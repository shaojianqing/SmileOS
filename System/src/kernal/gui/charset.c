#include "../type/type.h"
#include "color.h"
#include "view/view.h"
#include "charset.h"

void printChar(View *view, u8 c, int x, int y, Color color)
{
    u8 d;
    int i=0;
    u8 *buffer = (*view).buffer;
    u8 *pos = (u8 *)(CHARSET_DATA_BASE + (int)c*16);
    for (i=0; i<16; ++i) {
        int p = ((y + i)*(*view).width + x)*3;
        d = *(pos + i);
        if (d & 0x80) {
            *(buffer + p) = color.blue;
            *(buffer + p + 1) = color.green;
            *(buffer + p + 2) = color.red;
        }
        if (d & 0x40) {
            *(buffer + p + 3) = color.blue;
            *(buffer + p + 4) = color.green;
            *(buffer + p + 5) = color.red;
        }
        if (d & 0x20) {
            *(buffer + p + 6) = color.blue;
            *(buffer + p + 7) = color.green;
            *(buffer + p + 8) = color.red;
        }
        if (d & 0x10) {
            *(buffer + p + 9) = color.blue;
            *(buffer + p + 10) = color.green;
            *(buffer + p + 11) = color.red;
        }
        if (d & 0x08) {
            *(buffer + p + 12) = color.blue;
            *(buffer + p + 13) = color.green;
            *(buffer + p + 14) = color.red;
        }
        if (d & 0x04) {
            *(buffer + p + 15) = color.blue;
            *(buffer + p + 16) = color.green;
            *(buffer + p + 17) = color.red;
        }
        if (d & 0x02) {
            *(buffer + p + 18) = color.blue;
            *(buffer + p + 19) = color.green;
            *(buffer + p + 20) = color.red;
        }
        if (d & 0x01) {
            *(buffer + p + 21) = color.blue;
            *(buffer + p + 22) = color.green;
            *(buffer + p + 23) = color.red;
        }
    }
}

void printString(View *view, char *string, int size, int x, int y, Color color) {
   int i=0;
   for (i=0;i<size;++i) {
      char c = *(string + i);
      int p = x + i*8;
      printChar(view, c, p, y, color);
   }
}

void printInteger(View *view, int value, int x, int y, Color color)
{
    if (value>0) {
        printInteger(view, value/10, x-8, y, color);
        printChar(view, (char)(value%10 + 48), x, y, color);
    } else if (value == 0) {
        printChar(view, '0', x, y, color);
    }
}

void printHexInteger(View *view, int value, int x, int y, Color color) 
{
	if (value>0) {
        printHexInteger(view, value/16, x-8, y, color);
		int letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=55;
		}
		printChar(view, (char)letter, x, y, color);
    } else {
		printChar(view, '0', x, y, color);
	}
}

void printHexByte(View *view, u8 value, int x, int y, Color color) 
{
		u8 letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=87;
		}
		printChar(view, (u8)letter, x, y, color);
		
		value /=16;
		letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=87;
		}
		printChar(view, (u8)letter, x-8, y, color);
}

void printCharTest(u8 *buffer, u8 c, int x, int y, Color color)
{
    u8 d;
    int i=0;
    u8 *pos = (u8 *)(CHARSET_DATA_BASE + (int)c*16);
    for (i=0; i<16; ++i) {
        int p = ((y + i)*1024+x)*3;
        d = *(pos + i);
        if (d & 0x80) {
            *(buffer + p) = color.blue;
            *(buffer + p + 1) = color.green;
            *(buffer + p + 2) = color.red;
        }
        if (d & 0x40) {
            *(buffer + p + 3) = color.blue;
            *(buffer + p + 4) = color.green;
            *(buffer + p + 5) = color.red;
        }
        if (d & 0x20) {
            *(buffer + p + 6) = color.blue;
            *(buffer + p + 7) = color.green;
            *(buffer + p + 8) = color.red;
        }
        if (d & 0x10) {
            *(buffer + p + 9) = color.blue;
            *(buffer + p + 10) = color.green;
            *(buffer + p + 11) = color.red;
        }
        if (d & 0x08) {
            *(buffer + p + 12) = color.blue;
            *(buffer + p + 13) = color.green;
            *(buffer + p + 14) = color.red;
        }
        if (d & 0x04) {
            *(buffer + p + 15) = color.blue;
            *(buffer + p + 16) = color.green;
            *(buffer + p + 17) = color.red;
        }
        if (d & 0x02) {
            *(buffer + p + 18) = color.blue;
            *(buffer + p + 19) = color.green;
            *(buffer + p + 20) = color.red;
        }
        if (d & 0x01) {
            *(buffer + p + 21) = color.blue;
            *(buffer + p + 22) = color.green;
            *(buffer + p + 23) = color.red;
        }
    }
}

void printHexByteTest(u8 *buffer, u8 value, int x, int y, Color color) 
{
		u8 letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=87;
		}
		printCharTest(buffer, (u8)letter, x, y, color);
		
		value /=16;
		letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=87;
		}
		printCharTest(buffer, (u8)letter, x-8, y, color);
}

void printHexIntegerTest(u8 *buffer, int value, int x, int y, Color color)
{
	if (value>0) {
        printHexIntegerTest(buffer, value/16, x-8, y, color);
		int letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=55;
		}
		printCharTest(buffer, (char)letter, x, y, color);
    }
}


