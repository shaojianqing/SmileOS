#include "../type/type.h"
#include "image.h"
#include "sheet.h"

Image* loadImageFromStorage(u32 sector)
{
    u8 *head = (u8 *)allocMemory(IMAGE_HEADER_SIZE);
    readHardDisk(sector, head, IMAGE_HEADER_SIZE);
    u16 *width = (u16 *)(head+4);
    u16 *height = (u16 *)(head+6);

    u32 size = (*width)*(*height)*SCREEN_DENSITY;
   	u8 *buffer = (u8 *)allocMemory(size);

	readHardDisk(sector, buffer, size);

    Image *image = (Image*)allocMemoryInPage(sizeof(Image));
    (*image).width = *width;
    (*image).height = *height;
    (*image).data = buffer+8;
    (*image).head = head;
    (*image).buffer = buffer;
    return image;
}
