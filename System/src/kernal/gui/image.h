#define IMAGE_HEADER_SIZE 8

#define READ_BLOCK_SIZE 0x10000

typedef struct Image
{
    u8 *head;

    u8 *data;

    u8 *buffer;

    u16 width;
	
	u16 height;

} Image;

Image* loadImageFromStorage(u32 sector);
