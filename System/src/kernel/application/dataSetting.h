#define barDataCount	6
#define lineDataCount	6

/* 
 * The BarData data structure represents one bar datagraph statictic data.
 * It contains the color data , corner data and specified value.
 */
typedef struct BarData
{
    Color startColor;

	Color endColor;

	Corner corner;

	u32 value;

} BarData;

/* 
 * The LineData data structure represents one line datagraph statictic data.
 * It contains the color data and specified value.
 */
typedef struct LineData
{
    Color color;

	u32 value;

} LineData;

/* 
 * The function to draw bar graph. It is assigned as the function pointer
 * variable.
 *
 * Parameters:
 * 		this: the graphPanel where to draw the bar graph..
 * Return:
 *		no return value.
 */
void drawBarGraph(GraphPanel *this);

/* 
 * The function to draw line graph. It is assigned as the function pointer
 * variable.
 *
 * Parameters:
 * 		this: the graphPanel where to draw the line graph..
 * Return:
 *		no return value.
 */
void drawLineGraph(GraphPanel *this);
