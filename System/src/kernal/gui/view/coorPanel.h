#define ORIGIN_X				 390
#define ORIGIN_Y		 		 240

typedef struct CoorPanel CoorPanel;

typedef struct CoorPanel
{
    View view;

	View *canvas;

	void (*initPanel)(CoorPanel *this);

	void (*drawFuncation)(CoorPanel *this);

} CoorPanel;

CoorPanel *createCoorPanel(int x, int y, int w, int h);

void initCoorPanel(CoorPanel *this);
