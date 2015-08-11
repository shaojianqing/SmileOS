typedef struct Button Button;

typedef struct ButtonEvent ButtonEvent;

typedef struct ButtonEvent
{
	Button *button;

	MouseEvent *event;

} ButtonEvent;
