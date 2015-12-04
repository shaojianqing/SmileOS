#define barDataCount	6
#define lineDataCount	6

typedef struct BarData
{
    Color startColor;

	Color endColor;

	Corner corner;

	u32 value;

} BarData;

typedef struct LineData
{
    Color color;

	u32 value;

} LineData;

void drawBarGraph(GraphPanel *this);

void drawLineGraph(GraphPanel *this);
