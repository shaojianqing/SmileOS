#define MOUSE_WIDTH 		12
#define MOUSE_HEIGHT		22
#define BUFFER_SIZE   		512

typedef struct MouseData
{
    signed char buf[3];

    unsigned char phase;

    int x, y;

    int btn;
} MouseData;

typedef struct MouseBuffer
{
    int p,q,size,free,flags;

    unsigned char  buf[BUFFER_SIZE];
} MouseBuffer;

void initMouseBuffer()
{
    MouseBuffer* mouseBuffer = (MouseBuffer *)0x21000; 
    mouseBuffer->size = BUFFER_SIZE;
    mouseBuffer->free = BUFFER_SIZE;
    mouseBuffer->flags = 0;
    mouseBuffer->p = 0;
    mouseBuffer->q = 0;
}

unsigned char getMouseData(MouseBuffer* mouseBuffer)
{
    unsigned char data;
    if (mouseBuffer->free == mouseBuffer->size) {
        return -1;
    }
    data = mouseBuffer->buf[mouseBuffer->q];
    mouseBuffer->q++;
    if (mouseBuffer->q == mouseBuffer->size) {
        mouseBuffer->q = 0;
    }
    mouseBuffer->free++;
    return data;
}

int mouseBufferStatus(MouseBuffer* mouseBuffer)
{
    return (mouseBuffer->size - mouseBuffer->free);
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
        (*sheet).x = 500;
        (*sheet).y = 360;
        (*sheet).width = MOUSE_WIDTH;
        (*sheet).height = MOUSE_HEIGHT;
        drawMouseMap((*sheet).buffer);
    }
}

void processMouseData(MouseData *mouseData, Sheet *mouse, int *mx, int *my)
{
    clearInterrupt();
    MouseBuffer* mouseBuffer = (MouseBuffer *)0x21000; 
    if (mouseBufferStatus(mouseBuffer) == 0) {
        setupInterruptHlt();
    } else {
        unsigned char data = getMouseData(mouseBuffer);
        setupInterrupt();

        unsigned char sign =  data;
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

            if (*mx>1024) {
                *mx=1024;
            }
            if (*mx<0) {
                *mx=0;
            }

            if (*my>768) {
                *my=768;
            }
            if (*my<0) {
                *my=0;
            }
            slideSheet(mouse, (*mx), (*my));
        }
    }
}
