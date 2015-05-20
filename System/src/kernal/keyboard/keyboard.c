typedef struct KeyBuffer
{
    int start;

    int end;

    unsigned char *buffer;
} KeyBuffer;

void processKeyData(Sheet *sheet)
{
    KeyBuffer *buffer = (KeyBuffer *)0x20c00;

    Color blockColor;
    blockColor.red = 66;
    blockColor.green = 66;
    blockColor.blue = 66;

    int end = (*buffer).end;
    char *key = (char *)(0x20c08 + end - 1);
    printChar(sheet, *key, 10*end, 20*(end/80), blockColor);


}
