#include "../const/const.h"
#include "../type/type.h"
#include "image.h"
#include "sheet.h"

static void retainSelf(Image *image);

static void releaseSelf(Image *image);

Image* loadImageFromStorage(u32 sector)
{
    u8 *head = (u8 *)alloc(IMAGE_HEADER_SIZE);
	readHardDisk(sector, head, IMAGE_HEADER_SIZE);
    u16 *width = (u16 *)(head+4);
    u16 *height = (u16 *)(head+6);
    u32 size = (*width)*(*height)*SCREEN_DENSITY;
   	u8 *buffer = (u8 *)allocPage(size);
	readHardDisk(sector, buffer, size);
	release((u32)head);

    Image *image = (Image*)alloc(sizeof(Image));
    (*image).width = *width;
    (*image).height = *height;
	(*image).reference = 1;
    (*image).data = buffer+8;
    (*image).head = buffer;
    (*image).buffer = buffer;

	(*image).retain = retainSelf;
	(*image).release = releaseSelf;
    return image;
}

static void retainSelf(Image *image)
{
	if (image!=null) {
		(*image).reference += 1;	
	}
}

static void releaseSelf(Image *image)
{
	if (image!=null) {
		(*image).reference -= 1;
		if ((*image).reference==0) {
			u32 size = ((*image).width)*((*image).height)*SCREEN_DENSITY;
			releasePage((u32)(*image).buffer, size);
			release((u32)image);
			
		}
	}
}
