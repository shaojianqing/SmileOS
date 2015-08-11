
typedef struct CoorPanel CoorPanel;

typedef struct CoorPanel
{
    View view;

	void (*initPanel)(CoorPanel *this);

} StartButton;

CoorPanel *createCoorPanel(int x, int y, int w, int h);

void initPanel(CoorPanel *this);
