
typedef struct Factory Factory;

typedef struct Button Button;

typedef ButtonStyle* (*ButtonStyleType)();

typedef struct Button
{
    View view;

	bool select;

	char title[16];

	int length;

	Factory *factory;

	ButtonStyleType buttonStyleType;

	void (*initButton)(Button *this, char *text, int length, ButtonStyleType buttonStyleType);

	void (*onMouseClick)(Button *this, MouseEvent *event);

	void (*selectButton)(Button *this, bool select);

	void (*buttonOnTimer)();

} Button;

Button *createButton(int x, int y, int w, int h, Factory *factory);

void initButton(Button *this, char *text, int length, ButtonStyleType buttonStyleType);
