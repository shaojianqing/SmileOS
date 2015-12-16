#define MAX_SUB_VIEW_NUM 64

typedef struct View View;

typedef struct Sheet Sheet;

typedef struct MouseEvent MouseEvent;

typedef struct View
{
    Sheet *sheet;

	View *parentView;

	View *subViewList[MAX_SUB_VIEW_NUM];

	u32 subViewNum;

	u32 reference;

	u8 *buffer;

	int x;
	
	int y;

	int z;

	int width;

	int height;

	bool visible;

	bool (*addSubView)(View *this, View *view);

	bool (*removeSubView)(View *this, View *view);

	void (*setBackgroundColor)(View *this, Color color);

	void (*clearView)(View *this);

	void (*deleteView)(View *this);

	void (*releaseView)(View *this);

	void (*retainView)(View *this);

	void (*refreshRectView)(View *this);

	void (*onMouseDown)(View *this, MouseEvent *event);
	
	void (*processMouseDownEvent)(View *this, MouseEvent *event);

} View;

View *createView(int x, int y, int width, int height);

View *initWithViewFunction(View *view, int x, int y, int width, int height);

void refreshViewRect(View *this, int x, int y, int w, int h, int z);

void fillViewToSheetRect(View *this);

