#define MAX_BUTTON_SIZE 32

#define MAX_BUTTON_EVENT 64

typedef struct Button Button;

typedef struct Factory Factory;

typedef struct ButtonEvent ButtonEvent;

typedef struct Factory
{
	Button *selectButtonList[MAX_BUTTON_SIZE];

	Button *deselectButtonList[MAX_BUTTON_SIZE];

	ButtonEvent buttonEventList[MAX_BUTTON_EVENT];

	int selectFree, deselectFree;

	int selectP, selectQ;

	int deselectP, deselectQ;

	int eventFree;

	int eventP, eventQ;

	void (*selectButton)(Factory *factory, Button *button);

	void (*processEvent)(Factory *factory, Button *button, MouseEvent *event);

	void (*deselectButton)(Factory *factory);

	void (*doProcessEvent)(Factory *factory);

	void (*changeButtonStatus)(Factory *factory);

    void (*onTimer)();

} Factory;

void initFactory(Factory *factory, void (*onTimer)());
