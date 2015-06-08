typedef struct MouseData
{
    signed char buf[3];

    unsigned char phase;

    int x, y;

    int btn;
} MouseData;

QueueBuffer mouseBuffer;

void intHandler2c()
{
	u8 data;
	outByte(PIC1_OCW2, 0x64);
	outByte(PIC0_OCW2, 0x62);
	data = inByte(PORT_KEYDATA);
	putQueueBuffer(&mouseBuffer, data);
	return;
}

void drawMouseMap(char *buffer)
{
    int mouseMap[MOUSE_HEIGHT][MOUSE_WIDTH] = {'@','~','~','~','~','~','~','~','~','~','~','~',
                                               '@','@','~','~','~','~','~','~','~','~','~','~',
                                               '@','#','@','~','~','~','~','~','~','~','~','~',
                                               '@','#','#','@','~','~','~','~','~','~','~','~',
                                               '@','#','#','#','@','~','~','~','~','~','~','~',
                                               '@','#','#','#','#','@','~','~','~','~','~','~',
                                               '@','#','#','#','#','#','@','~','~','~','~','~',
                                               '@','#','#','#','#','#','#','@','~','~','~','~',
                                               '@','#','#','#','#','#','#','#','@','~','~','~',
                                               '@','#','#','#','#','#','#','#','#','@','~','~',
                                               '@','#','#','#','#','#','#','#','#','#','@','~',
                                               '@','#','#','#','#','#','#','@','@','@','@','@',
                                               '@','#','#','#','@','#','#','@','~','~','~','~',
                                               '@','#','#','@','@','#','#','@','~','~','~','~',
                                               '@','#','@','~','~','@','#','#','@','~','~','~',
                                               '@','@','~','~','~','@','#','#','@','~','~','~',
                                               '@','~','~','~','~','~','@','#','#','@','~','~',
                                               '~','~','~','~','~','~','@','#','#','@','~','~',
                                               '~','~','~','~','~','~','~','@','#','#','@','~',
                                               '~','~','~','~','~','~','~','@','#','#','@','~',
                                               '~','~','~','~','~','~','~','~','@','@','~','~'
                                              };

    int i=0, j=0;
    for (i=0; i<21; ++i) {
        for (j=0; j<MOUSE_WIDTH; ++j) {
            if (mouseMap[i][j] == '@') {
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY) = 20;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 1) = 20;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 2) = 20;
            } else if (mouseMap[i][j] == '#') {
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY) = 255;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 1) = 255;
                *(buffer + (MOUSE_WIDTH*i + j)*SCREEN_DENSITY + 2) = 255;
            }
        }
    }
}

Sheet *prepareMouseSheet(Sheet* sheet)
{
    if (sheet != 0) {
        (*sheet).buffer = (char *)allocMemoryInPage(MOUSE_WIDTH*MOUSE_HEIGHT*SCREEN_DENSITY);
        (*sheet).x = 640;
        (*sheet).y = 512;
        (*sheet).width = MOUSE_WIDTH;
        (*sheet).height = MOUSE_HEIGHT;
        drawMouseMap((*sheet).buffer);
    }
}

void processMouseData(MouseData *mouseData, Sheet *mouse, int *mx, int *my)
{
    setupInterrupt();
    u8 sign = getQueueBuffer(&mouseBuffer);
    setupInterrupt();
    if ((*mouseData).phase == 0) {
        if (sign == 0xfa) {
            (*mouseData).phase = 1;
        }
    } else if ((*mouseData).phase == 1) {
        if ((sign & 0xc8) == 0x08) {
            (*mouseData).buf[0] = sign;
            (*mouseData).phase = 2;
        }
    } else if ((*mouseData).phase == 2) {
        (*mouseData).buf[1] = sign;
        (*mouseData).phase = 3;
    } else if ((*mouseData).phase == 3) {
        (*mouseData).buf[2] = sign;
        (*mouseData).phase = 1;
        (*mouseData).btn = (*mouseData).buf[0] & 0x07;
        (*mouseData).x = (*mouseData).buf[1];
        (*mouseData).y = (*mouseData).buf[2];

        if (((*mouseData).buf[0] & 0x10) != 0) {
            (*mouseData).x |= 0xffffff00;
        }

        if (((*mouseData).buf[0] & 0x20) != 0) {
            (*mouseData).y |= 0xffffff00;
        }

        (*mouseData).y = 0 - (*mouseData).y;

        Color color;
        color.red = 0x00;
        color.green =0x99;
        color.blue = 0xff;

        *mx += (*mouseData).x;
        *my += (*mouseData).y;

        if (*mx>SCREEN_WIDTH) {
            *mx=SCREEN_WIDTH;
        }
        if (*mx<0) {
            *mx=0;
        }

        if (*my>SCREEN_HEIGHT) {
            *my=SCREEN_HEIGHT;
        }
        if (*my<0) {
            *my=0;
        }
        slideSheet(mouse, (*mx), (*my));
    }
}
