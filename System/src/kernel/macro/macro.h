/* 
 * The Maximum macro between two values.
 *
 * Parameters:
 * 		a: the value one.
 *		b: the value two.
 * Return:
 *		the maximum value.
 */
#define max(a,b)	((a)>(b)?(a):(b))

/* 
 * The Minimum macro between two values.
 *
 * Parameters:
 * 		a: the value one.
 *		b: the value two.
 * Return:
 *		the Minimum value.
 */
#define min(a,b)	((a)<(b)?(a):(b))

/* 
 * The LBA address transforming macro.
 *
 * Parameters:
 * 			lba: the lba address.
 *			drv: the device no.
 *	lba_highest: the sign of lba.
 * Return:
 *		the transformed address.
 */
#define	MAKE_DEVICE_REG(lba,drv,lba_highest) (((lba) << 6) |		\
					      ((drv) << 4) |		\
					      (lba_highest & 0xF) | 0xA0)
