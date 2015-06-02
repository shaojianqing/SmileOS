#define max(a,b)	((a)>(b)?(a):(b))
#define min(a,b)	((a)<(b)?(a):(b))

#define	MAKE_DEVICE_REG(lba,drv,lba_highest) (((lba) << 6) |		\
					      ((drv) << 4) |		\
					      (lba_highest & 0xF) | 0xA0)
