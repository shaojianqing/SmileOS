#define IMAGE_HEADER_SIZE 8

#define READ_BLOCK_SIZE 0x10000

typedef struct Image
{
    char *head;

    char *data;

    char *buffer;

    unsigned short width, height;

    unsigned int x, y;

} Image;

Image* loadImageFromStorage(u32 sector)
{
    u8 *head = (u8 *)allocMemory(IMAGE_HEADER_SIZE);
    readHardDisk(sector, head, IMAGE_HEADER_SIZE);
    u16 *width = (u16 *)(head+4);
    u16 *height = (u16 *)(head+6);
    freeMemory((u32)head, IMAGE_HEADER_SIZE);

    u32 size = (*width)*(*height)*SCREEN_DENSITY;
   	u8 *buffer = (u8 *)allocMemory(size);

	readHardDisk(sector, buffer, size);

    Image *image = (Image*)allocMemoryInPage(sizeof(Image));
    (*image).width = 1024;
    (*image).height = 768;
    (*image).x = 0;
    (*image).y = 0;
    (*image).data = buffer+8;
    (*image).head = head;
    (*image).buffer = buffer;
    return image;
}

void addImage(Sheet* sheet, Image* image)
{
    unsigned short height=(*image).height, width=(*image).width;
    unsigned int sheetWidth = (*sheet).width;

    unsigned int x=0, y=0;
    for (y=0; y<height; ++y) {
        for (x=0; x<width; ++x) {
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3) = *((*image).data+(y*80+x)*3);
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3+1) = *((*image).data+(y*80+x)*3+1);
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3+2) = *((*image).data+(y*80+x)*3+2);
        }
    }
}
