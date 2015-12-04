
typedef struct GridPanel GridPanel;

typedef GridDataItem *(*ItemRender)(GridPanel *this, u32 index, int width, int height);

typedef struct GridPanel
{
    View view;

	Object *dataList;

	u32 dataCount;

	void (*initPanel)(GridPanel *this, HeaderItem *itemList, u32 headerCount);

	void (*renderDataGrid)(GridPanel *this, u32 dataSize, ItemRender itemRender);

} GridPanel;

GridPanel *createGridPanel(int x, int y, int w, int h);
