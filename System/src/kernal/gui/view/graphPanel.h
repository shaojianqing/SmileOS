
typedef struct GraphPanel GraphPanel;

typedef struct GraphPanel
{
    View view;

	View *canvas;

	void (*initPanel)(GraphPanel *this);

	void (*drawGraph)(GraphPanel *this);

} GraphPanel;

GraphPanel *createGraphPanel(int x, int y, int w, int h);

void initGraphPanel(GraphPanel *this);
