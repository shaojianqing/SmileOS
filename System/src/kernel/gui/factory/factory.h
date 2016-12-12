#define MAX_BUTTON_SIZE 32

#define MAX_BUTTON_EVENT 64

struct Button;

struct ButtonEvent;

typedef struct Factory Factory;

struct Factory
{
	struct Button *selectButtonList[MAX_BUTTON_SIZE];

	struct Button *deselectButtonList[MAX_BUTTON_SIZE];

	struct ButtonEvent buttonEventList[MAX_BUTTON_EVENT];

	int selectFree, deselectFree;

	int selectP, selectQ;

	int deselectP, deselectQ;

	int eventFree;

	int eventP, eventQ;

	void (*selectButton)(Factory *factory, struct Button *button);

	void (*processEvent)(Factory *factory, struct Button *button, MouseEvent *event);

	void (*deselectButton)(Factory *factory);

	void (*doProcessEvent)(Factory *factory);

	void (*changeButtonStatus)(Factory *factory);

    void (*onTimer)();

};

void initFactory(Factory *factory, void (*onTimer)());
