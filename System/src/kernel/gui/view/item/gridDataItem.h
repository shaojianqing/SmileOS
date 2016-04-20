
#define 		GRID_DATA_ITEM_HEIGHT		32

typedef struct GridDataItem GridDataItem;

typedef struct GridDataItem
{
    View view;

	bool reusable;

} GridDataItem;

GridDataItem *createGridDataItem(int w, int h);
