#include "../const/const.h"
#include "../type/type.h"
#include "../algorithm/algorithm.h"
#include "../gui/color.h"
#include "../gui/sheet.h"
#include "keyboard.h"

extern QueueBuffer systemBuffer;

void intHandler21()
{
	outByte(PIC0_OCW2, 0x61);
	u8 data = inByte(PORT_KEYDATA);
	putQueueBuffer(&systemBuffer, data+1024);
	return;
}

void initKeyTableSetting()
{
	keyTable[0x00] =  0;
	keyTable[0x01] =  0;
	keyTable[0x02] = '1';

	keyTable[0x03] = '2';
	keyTable[0x04] = '3';
	keyTable[0x05] = '4';

	keyTable[0x06] = '5';
	keyTable[0x07] = '6';
	keyTable[0x08] = '7';

	keyTable[0x09] = '8';
	keyTable[0x0a] = '9';
	keyTable[0x0b] = '0';

	keyTable[0x0c] = '-';
	keyTable[0x0d] = '^';
	keyTable[0x0e] =  0;

	keyTable[0x0f] =  0;
	keyTable[0x10] = 'Q';
	keyTable[0x11] = 'W';

	keyTable[0x12] = 'E';
	keyTable[0x13] = 'R';
	keyTable[0x14] = 'T';

	keyTable[0x15] = 'Y';
	keyTable[0x16] = 'U';
	keyTable[0x17] = 'I';

	keyTable[0x18] = 'O';
	keyTable[0x19] = 'P';
	keyTable[0x1a] = '@';

	keyTable[0x1b] = '[';
	keyTable[0x1c] = 0;
	keyTable[0x1d] = 0;

	keyTable[0x1e] = 'A';
	keyTable[0x1f] = 'S';
	keyTable[0x20] = 'D';

	keyTable[0x21] = 'F';
	keyTable[0x22] = 'G';
	keyTable[0x23] = 'H';

	keyTable[0x24] = 'J';
	keyTable[0x25] = 'K';
	keyTable[0x26] = 'L';

	keyTable[0x27] = ';';
	keyTable[0x28] = ':';
	keyTable[0x29] =  0;

	keyTable[0x2a] =  0;
	keyTable[0x2b] = ']';
	keyTable[0x2c] = 'Z';

	keyTable[0x2d] = 'X';
	keyTable[0x2e] = 'C';
	keyTable[0x2f] = 'V';

	keyTable[0x30] = 'B';
	keyTable[0x31] = 'N';
	keyTable[0x32] = 'M';

	keyTable[0x33] = ',';
	keyTable[0x34] = '.';
	keyTable[0x35] = '/';

	keyTable[0x36] =  0;
	keyTable[0x37] = '*';
	keyTable[0x38] =  0;

	keyTable[0x39] = ' ';
	keyTable[0x3a] =  0;
	keyTable[0x3b] =  0;

	keyTable[0x3c] =  0;
	keyTable[0x3d] =  0;
	keyTable[0x3e] =  0;

	keyTable[0x3f] =  0;
	keyTable[0x40] =  0;
	keyTable[0x41] =  0;

	keyTable[0x42] =  0;
	keyTable[0x43] =  0;
	keyTable[0x44] =  0;

	keyTable[0x45] =  0;
	keyTable[0x46] =  0;
	keyTable[0x47] = '7';

	keyTable[0x48] = '8';
	keyTable[0x49] = '9';
	keyTable[0x4a] = '-';

	keyTable[0x4b] = '4';
	keyTable[0x4c] = '5';
	keyTable[0x4d] = '6';

	keyTable[0x5e] = '+';
	keyTable[0x4f] = '1';
	keyTable[0x50] = '2';

	keyTable[0x51] = '3';
	keyTable[0x52] = '0';
	keyTable[0x53] = '.';
}

void processKeyData(KeyData *keyData, u32 data, Sheet *sheet) 
{
	u32 key = data-1024;

		Color txtMainColor;
        txtMainColor.red = 250;
        txtMainColor.green = 250;
        txtMainColor.blue = 250;

	if (key<0x54) {
		u8 ascii = keyTable[key];
		if (ascii != 0) {
			Color mainColor;
			mainColor.red = 160;
			mainColor.green = 80;
			mainColor.blue = 30;
			charX+=8;
			drawRect((*sheet).buffer, sheet, 204+charX, 210, 204+charX+8, 210+16, txtMainColor);
			printChar(sheet, ascii, 204+charX, 210, mainColor);
		}		
	} 

	if (key==0x0e && charX>=8) {		
		drawRect((*sheet).buffer, sheet, 204+charX, 210, 204+charX+16, 210+16, txtMainColor);
		charX-=8;	
	}	
	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
	refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
	
	setupInterrupt();
}

void showCursor(Sheet *sheet)
{
	Color cursorColor;
    cursorColor.red = 30;
    cursorColor.green = 30;
    cursorColor.blue = 30;

	drawRect((*sheet).buffer, sheet, 204+charX+8, 210, 204+charX+16, 210+16, cursorColor);
	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
	refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}

void hideCursor(Sheet *sheet)
{
	Color cursorColor;
    cursorColor.red = 250;
    cursorColor.green = 250;
    cursorColor.blue = 250;

	drawRect((*sheet).buffer, sheet, 204+charX+8, 210, 204+charX+16, 210+16, cursorColor);
	refreshSheetMap((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, 0);
	refreshSheetSub((*sheet).x, (*sheet).y, (*sheet).x+(*sheet).width, (*sheet).y+(*sheet).height, (*sheet).z, (*sheet).z);
}
