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

Image* loadImageFromStorage(u32 sector);
