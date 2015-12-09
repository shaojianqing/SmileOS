#include "../../../const/const.h"
#include "../../../type/type.h"
#include "../../color.h"
#include "../view.h"
#include "gridDataItem.h"

GridDataItem *createGridDataItem(int w, int h)
{
	GridDataItem *gridDataItem = (GridDataItem *)alloc(sizeof(GridDataItem));
	gridDataItem = (GridDataItem *)initWithViewFunction((View*)gridDataItem, 0, 0, w, h);

	return gridDataItem;
}
