void printChar(Sheet *sheet, char c, int x, int y, Color color)
{
    char d;
    int i=0;
    char *buffer = (*sheet).buffer;
    char *pos = (char *)(0x19400 + (int)c*16);
    for (i=0; i<16; ++i)
    {
        int p = ((y + i)*(*sheet).width + x)*3;
        d = *(pos + i);
        if (d & 0x80)
        {
            *(buffer + p) = color.blue;
            *(buffer + p + 1) = color.green;
            *(buffer + p + 2) = color.red;
        }
        if (d & 0x40)
        {
            *(buffer + p + 3) = color.blue;
            *(buffer + p + 4) = color.green;
            *(buffer + p + 5) = color.red;
        }
        if (d & 0x20)
        {
            *(buffer + p + 6) = color.blue;
            *(buffer + p + 7) = color.green;
            *(buffer + p + 8) = color.red;
        }
        if (d & 0x10)
        {
            *(buffer + p + 9) = color.blue;
            *(buffer + p + 10) = color.green;
            *(buffer + p + 11) = color.red;
        }
        if (d & 0x08)
        {
            *(buffer + p + 12) = color.blue;
            *(buffer + p + 13) = color.green;
            *(buffer + p + 14) = color.red;
        }
        if (d & 0x04)
        {
            *(buffer + p + 15) = color.blue;
            *(buffer + p + 16) = color.green;
            *(buffer + p + 17) = color.red;
        }
        if (d & 0x02)
        {
            *(buffer + p + 18) = color.blue;
            *(buffer + p + 19) = color.green;
            *(buffer + p + 20) = color.red;
        }
        if (d & 0x01)
        {
            *(buffer + p + 21) = color.blue;
            *(buffer + p + 22) = color.green;
            *(buffer + p + 23) = color.red;
        }
    }
}

/*void printString(char *string, int size, int x, int y, Color color) {
   int i=0;
   for (i=0;i<size;++i) {
      char c = *(string + i);
      int p = x + i*8;
      printChar(c, p, y, color);
   }
}*/

void printInteger(Sheet *sheet, int value, int x, int y, Color color)
{
    if (value>0)
    {
        printInteger(sheet, value/10, x-8, y, color);
        printChar(sheet, (char)(value%10 + 48), x, y, color);
    }
    else if (value == 0)
    {
        printChar(sheet, '0', x, y, color);
    }
}


