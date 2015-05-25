#define 	ATA_READ		0x20
#define 	ATA_WRITE		0x30
#define		SECTOR_SIZE		512
#define		HD_TIMEOUT		1000

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

typedef struct HdCmd
{
    u8 features;
	
	u8 count;

	u8 lbaLow;

	u8 lbaMid;

	u8 lbaHigh;

	u8 device;

	u8 command;
} HdCmd;

bool isHardDiskReady=FALSE;

void intHandler2e()
{
	inByte(REG_STATUS);
	isHardDiskReady=TRUE;
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

bool sendHdCmd(HdCmd *cmd)
{
	if (waitForStatus(STATUS_BSY, 0, HD_TIMEOUT) == TRUE) {
		outByte(REG_DEV_CTRL, 0);
		outByte(REG_FEATURES, cmd->features);
		outByte(REG_NSECTOR, cmd->count);
		outByte(REG_LBA_LOW, cmd->lbaLow);
		outByte(REG_LBA_MID, cmd->lbaMid);
		outByte(REG_LBA_HIGH, cmd->lbaHigh);
		outByte(REG_DEVICE, cmd->device);
		outByte(REG_CMD, cmd->command);
		return TRUE;
	} else {
		return FALSE;	
	}
}

void readHardDisk(int sector, void *buffer, int size)
{
	HdCmd cmd;
	cmd.features = 0;
	cmd.count = (size+SECTOR_SIZE-1)/SECTOR_SIZE;
	cmd.lbaLow = sector & 0xFF;
	cmd.lbaMid = (sector>>8) & 0xFF;
	cmd.lbaHigh = (sector>>16) & 0xFF;
	cmd.device = ((sector>>24) & 0x0F) | 0xE0;
	cmd.command = ATA_READ;
	isHardDiskReady = FALSE;
	if (sendHdCmd(&cmd) == TRUE) {
		while(size>0) {
			waitForHdInterrupt();
			int bytes = min(SECTOR_SIZE, size);
			readPort(REG_DATA, buffer, bytes);
			buffer+=bytes;			
			size-=bytes;
		}
	}
}

