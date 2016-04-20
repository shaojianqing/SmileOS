#include "../type/type.h"
#include "color.h"
#include "view/view.h"
#include "charset.h"

void printChar(View *view, u8 c, int x, int y, Color mainColor, Color shadowColor)
{
    u8 data = 0;
    u32 i=0, j=0;
    u8 *buffer = (*view).buffer;
	u32 point = 0;
    u8 *pos = (u8 *)(CHARSET_DATA_BASE + (u32)c*CHARSET_HEIGHT*CHARSET_WIDTH);
    for (i=0; i<CHARSET_HEIGHT; ++i) {
		for (j=0; j<CHARSET_WIDTH; ++j) {
			data = *(pos + i*CHARSET_WIDTH + j);
			if (data=='*') {
				point = ((y + i)*(*view).width + x + j)*3;
				*(buffer + point) = mainColor.blue;
            	*(buffer + point + 1) = mainColor.green;
            	*(buffer + point + 2) = mainColor.red;
			} else if (data=='~') {
				point = ((y + i)*(*view).width + x + j)*3;
				*(buffer + point) = shadowColor.blue;
            	*(buffer + point + 1) = shadowColor.green;
            	*(buffer + point + 2) = shadowColor.red;		
			}	
		}
    }
}

void printString(View *view, char *string, int size, int x, int y, Color mainColor, Color shadowColor) {
   int i=0;
   for (i=0;i<size;++i) {
      char c = *(string + i);
      int p = x + i*8;
      printChar(view, c, p, y, mainColor, shadowColor);
   }
}

void printInteger(View *view, int value, int x, int y, Color mainColor, Color shadowColor)
{
    if (value>0) {
        printInteger(view, value/10, x-8, y, mainColor, shadowColor);
        printChar(view, (char)(value%10 + 48), x, y, mainColor, shadowColor);
    } else if (value == 0) {
        printChar(view, '0', x, y, mainColor, shadowColor);
    }
}

void printHexInteger(View *view, int value, int x, int y, Color mainColor, Color shadowColor) 
{
	if (value>0) {
        printHexInteger(view, value/16, x-8, y, mainColor, shadowColor);
		int letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=55;
		}
		printChar(view, (char)letter, x, y, mainColor, shadowColor);
    } else {
		printChar(view, '0', x, y, mainColor, shadowColor);
	}
}

void printHexByte(View *view, u8 value, int x, int y, Color mainColor, Color shadowColor) 
{
		u8 letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=87;
		}
		printChar(view, (u8)letter, x, y, mainColor, shadowColor);
		
		value /=16;
		letter = value%16;
		if (letter<10) {
			letter+=48;
 		} else {
			letter+=87;
		}
		printChar(view, (u8)letter, x-8, y, mainColor, shadowColor);
}
