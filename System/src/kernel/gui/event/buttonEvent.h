
struct Button;

struct MouseEvent;

typedef struct ButtonEvent ButtonEvent;

struct ButtonEvent
{
	struct Button *button;

	struct MouseEvent *event;
};
