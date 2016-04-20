
typedef struct GridPanel GridPanel;

/* 
 * The render function pointer type, with which gridPanel can render all kinds of 
 * datagrid, if only the function pointer tells how to render the data row.
 */
typedef GridDataItem *(*ItemRender)(GridPanel *this, u32 index, int width, int height);

/* 
 * The GridPanel data structure represents the GridPanel class.
 * It extends the View class, and is designed to draw the particular
 * dataGrid.
 */
typedef struct GridPanel
{
    View view;

	Object *dataList;

	u32 dataCount;

	/* 
	 * Initialize one gridPanel object with the specified parameters.
	 * 
	 * Parameters:
	 *	   this: the gridPanel object itself.
	 * itemList: the headerItem list of the grid.
     * headerCount: the count of the headerItem list.
	 * Return:
	 *		no return value.
	 */
	void (*initPanel)(GridPanel *this, HeaderItem *itemList, u32 headerCount);

	/* 
	 * The render function pointer variable of the panel with which
     * the panel can render the particular datagrid.
	 * 
	 * Parameters:
	 *	   this: the coorPanel object itself.
	 * dataSize: the size of the datalist to be rendered.
     * itemRender: the render function pointer with which the panel can render the data row.
	 * Return:
	 *		no return value.
	 */
	void (*renderDataGrid)(GridPanel *this, u32 dataSize, ItemRender itemRender);

} GridPanel;

/* 
 * Create and initialize one gridPanel object with the specified
 * parameters.
 *
 * Parameters:
 * 		 x: the x axis of the graphPanel in the parent container.
 *		 y: the y axis of the graphPanel in the parent container.
 *		 w: the width of the graphPanel in the parent container.
 *		 h: the height of the graphPanel in the parent container.
 * Return:
 *		GridPanel pointer.
 */
GridPanel *createGridPanel(int x, int y, int w, int h);
