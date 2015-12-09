
typedef struct StartButton StartButton;

typedef struct StartButton
{
    View view;

	void (*initWithImage)(StartButton *this, Image *image);

} StartButton;

StartButton *createStartButton(int x, int y, int w, int h, u32 sector);
