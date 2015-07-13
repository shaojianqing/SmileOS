#define SHEET_MANAGE_TABLE 0x28800
#define MAP_ADDRESS 0x100000

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_DENSITY 3

#define TRANSPARENT 0x00

#define SHEET_NUM 512

typedef struct Image Image;

typedef struct Sheet
{
    char *buffer;

    int x, y, width, height, z, status;

} Sheet;

typedef struct SheetManager
{
    u16 sheetNum;

    Sheet *sheets[SHEET_NUM];

    Sheet sheetList[SHEET_NUM];

} SheetManager;

void initSheetManagement();

Sheet* prepareSheet();

void refreshSheetMap(int x1, int y1, int x2, int y2, int z1);

void refreshSheetSub(int x1, int y1, int x2, int y2, int z1, int z2);

void loadSheet(Sheet *sheet, int z);

void slideSheet(Sheet *sheet, int x, int y);

void releaseSheet(Sheet *sheet);

void resetSheet(Sheet *sheet);

void addImage(Sheet* sheet, Image* image);
