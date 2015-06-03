#define 	ATA_IDENTIFY		0xEC
#define 	ATA_READ		0x20
#define 	ATA_WRITE		0x30
#define		SECTOR_SIZE		512
#define		HD_TIMEOUT		10000

#define 	REG_DATA		0x1F0		
#define 	REG_FEATURES	0x1F1		
#define	 	REG_ERROR		REG_FEATURES
#define 	REG_NSECTOR		0x1F2		
#define 	REG_LBA_LOW		0x1F3		
#define 	REG_LBA_MID		0x1F4		
#define 	REG_LBA_HIGH	0x1F5
#define 	REG_DEVICE		0x1F6
#define 	REG_STATUS		0x1F7
#define 	REG_CMD			REG_STATUS
#define 	REG_DEV_CTRL	0x3F6
#define 	REG_ALT_STATUS	REG_DEV_CTRL
#define 	REG_DRV_ADDR	0x3F7
	
#define		STATUS_BSY		0x80
#define		STATUS_DRDY		0x40
#define		STATUS_DFSE		0x20
#define		STATUS_DSC		0x10
#define		STATUS_DRQ		0x08
#define		STATUS_CORR		0x04
#define		STATUS_IDX		0x02
#define		STATUS_ERR		0x01

typedef struct HdCommand
{
    u8 features;
	
	u8 count;

	u8 lbaLow;

	u8 lbaMid;

	u8 lbaHigh;

	u8 device;

	u8 command;
} HdCommand;

HdCommand command;

bool isHardDiskReady = FALSE;

void intHandler2e()
{
	inByte(REG_STATUS);
	outByte(0x20, 0xA0);
	isHardDiskReady = TRUE;
	return;
}

bool waitForStatus(int mask, int val, int timeout) 
{
	long time = getTime();
	while((getTime() - time)<timeout) {
		if ((inByte(REG_STATUS) & mask) == val)	{
			return TRUE;	
		}
	}
	return FALSE;
}

bool waitForHdInterrupt()
{
	while(TRUE) {
		if (isHardDiskReady==TRUE) {
			return TRUE;
		}
	}
	return FALSE;
}

bool sendHdCommand(HdCommand *command)
{
	if (waitForStatus(STATUS_BSY, 0, HD_TIMEOUT) == TRUE) {
		outByte(REG_DEV_CTRL, 0);
		outByte(REG_FEATURES, command->features);
		outByte(REG_NSECTOR, command->count);
		outByte(REG_LBA_LOW, command->lbaLow);
		outByte(REG_LBA_MID, command->lbaMid);
		outByte(REG_LBA_HIGH, command->lbaHigh);
		outByte(REG_DEVICE, command->device);

		outByte(REG_CMD, command->command);

		return TRUE;
	} else {
		return FALSE;	
	}
}

void readHardSector(u32 sector, u8 *buffer, int sectorCount)
{
  	command.features = 0;
	command.count = sectorCount;
	command.lbaLow	= sector & 0xFF;
	command.lbaMid	= (sector >>  8) & 0xFF;
	command.lbaHigh	= (sector >> 16) & 0xFF;

	command.device = MAKE_DEVICE_REG(1, 0, (sector >> 24) & 0xF);
	command.command = ATA_READ;
	
	isHardDiskReady = FALSE;
	sendHdCommand(&command);
	int sectorLeft = command.count;
	while (sectorLeft>0) {
		waitForStatus(STATUS_BSY, 0, HD_TIMEOUT);
		readPort(REG_DATA, buffer, 512);
		buffer+=512;
		sectorLeft--;
	}
}

void readHardDisk(u32 sector, u8 *buffer, int size)
{
	while(size>0) {
		int sectorCount = (size/512)>255?255:(size/512+1);
		readHardSector(sector, buffer, sectorCount);
		sector += sectorCount;
		buffer += sectorCount*512;
		size -=  sectorCount*512;
	}
}


