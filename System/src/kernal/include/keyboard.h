u8 keyTable[0x54];

int charX;

typedef struct KeyData
{
    int key;
} KeyData;

void intHandler21();

void initKeyTableSetting();

void processKeyData(KeyData *keyData, u32 data, Sheet *sheet);

void showCursor(Sheet *sheet);

void hideCursor(Sheet *sheet);
