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

Image* loadImageFromStorage(unsigned int sector)
{
    char *head = (char *)allocMemory(IMAGE_HEADER_SIZE);
    readHardDisk(sector, head, IMAGE_HEADER_SIZE);
    unsigned short *width = (unsigned short *)(head+4);
    unsigned short *height = (unsigned short *)(head+6);
    freeMemory((unsigned int)head, IMAGE_HEADER_SIZE);

    unsigned int size = (*width)*(*height)*SCREEN_DENSITY+8;
    unsigned char *buffer = (unsigned char *)allocMemoryInPage(size);

    int page = 0;
    if (size%READ_BLOCK_SIZE==0)
    {
        page = size/READ_BLOCK_SIZE;
    }
    else
    {
        page = size/READ_BLOCK_SIZE+1;
    }
    unsigned int i=0, pageSize=0;
    for (i=0; i<page; ++i)
    {
        pageSize = (i<page-1?READ_BLOCK_SIZE:size-i*READ_BLOCK_SIZE);
        readHardDisk(sector, buffer, pageSize);
        buffer+=pageSize;
        sector+=0x80;
    }

    Image *image = (Image*)allocMemoryInPage(sizeof(Image));
    (*image).width = *width;
    (*image).height = *height;
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
    for (y=0; y<height; ++y)
    {
        for (x=0; x<width; ++x)
        {
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3) = *((*image).data+(y*80+x)*3);
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3+1) = *((*image).data+(y*80+x)*3+1);
            *((*sheet).buffer+((y+(*image).y)*sheetWidth+x+(*image).x)*3+2) = *((*image).data+(y*80+x)*3+2);
        }
    }
}
