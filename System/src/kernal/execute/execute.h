
#define ELF_IDENT_SIZE 			16

#define FLAG_ELF_CODE 			0x05
#define FLAG_ELF_DATA 			0x06
#define FLAG_ELF_STACK 			0x07

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

typedef struct ExecutableFile
{
	ElfFileHeader *header;

	ElfProgramHeader *codeHeader;

	ElfProgramHeader *dataHeader;

	ElfProgramHeader *stackHeader;

	u32 executeSize;

	u8 *executeBuffer;
	
} ExecutableFile;

ExecutableFile* loadExecuteFromStorage(u32 sector);















