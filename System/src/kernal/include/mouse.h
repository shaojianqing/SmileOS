#define MOUSE_WIDTH 			12
#define MOUSE_HEIGHT			22

typedef struct MouseData
{
    signed char buf[3];

    u8 phase;

    int x, y;

    int btn;
} MouseData;

void intHandler2c();

void processMouseData(MouseData *mouseData, u32 data, Sheet *mouse, int *mx, int *my);
