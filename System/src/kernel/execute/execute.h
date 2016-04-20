
/* 
 * The size of the elf file identifier.
 */
#define ELF_IDENT_SIZE 			16

/* 
 * The flag of the elf header type.
 */
#define FLAG_ELF_CODE 			0x05
#define FLAG_ELF_DATA 			0x06
#define FLAG_ELF_STACK 			0x07

/* 
 * The ELF file header data struture represents the file header of the elf
 * file which is based on the definition of the elf specification precisely.
 */
typedef struct ElfFileHeader
{
	u8 identity[ELF_IDENT_SIZE];

	u16 type;

	u16 machine;

	u32 version;

	u32 entry;

	u32 phOffset;

	u32 shOffset;

	u32 flags;

	u16 headerSize;

	u16 phentSize;

	u16 phNum;

	u16 shentSize;

	u16 shNum;

	u16 shStrIndex;	

} ElfFileHeader;

/* 
 * The ELF program header data struture represents the program header of the elf
 * file which is based on the definition of the elf specification precisely.
 */
typedef struct ElfProgramHeader
{	
	u32 type;

	u32 offset;

	u32 virtialAddr;

	u32 physicalAddr;

	u32 fileSize;

	u32 memorySize;

	u32 flags;

	u32 align;

} ElfProgramHeader;

/* 
 * The ExecutableFile data struture represents the elf executable file memory
 * image, it contains the headers, size and complete memory buffer.
 */
typedef struct ExecutableFile
{
	ElfFileHeader *header;

	ElfProgramHeader *codeHeader;

	ElfProgramHeader *dataHeader;

	ElfProgramHeader *stackHeader;

	u32 executeSize;

	u8 *executeBuffer;
	
} ExecutableFile;

/* 
 * Load the elf file data at the specified sector position and analysis it, finally
 * create one executable file memory image in the memory.
 *
 * Parameters:
 * 		sector: the starting sector position of the elf file data in the harddisk.
 * Return:
 *		the executablefile pointer that is used to create one process image.
 */
ExecutableFile* loadExecuteFromStorage(u32 sector);
