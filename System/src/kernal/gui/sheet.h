#define SHEET_MANAGE_TABLE 0x29800
#define MAP_ADDRESS 0x100000

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_DENSITY 3

#define TRANSPARENT 0x00

#define STATUS_SHEET_UNUSE 0
#define STATUS_SHEET_USING 1

#define SHEET_NUM 256

typedef struct View View;

typedef struct Image Image;

typedef struct Process Process;

typedef struct Sheet
{
    u8 *buffer;

    int x, y;

	int width, height;

	int z, status;

	View *contentView;

	Process *process;

} Sheet;

typedef struct SheetManager
{
    u8 sheetNum;

    Sheet *sheets[SHEET_NUM];

    Sheet sheetList[SHEET_NUM];

} SheetManager;

void initSheetManagement();

Sheet* prepareSheet();

bool isSheetTop(Sheet *sheet);

void setSheetTop(Sheet *sheet);

Sheet* getCurrentSheet(int x, int y);

void loadContentView(Sheet *sheet, View *view);

void refreshSheetRect(Sheet *sheet, int x, int y, int w, int h);

void initMouseSheet(Sheet *sheet);

void loadWindowSheet(Sheet *sheet);

void initBackgroundSheet(Sheet *sheet);

void slideSheet(Sheet *sheet, int x, int y);

void processSheetMouseDownEvent(Sheet *sheet, int x, int y);

void releaseSheet(Sheet *sheet);

void resetSheet(Sheet *sheet);

