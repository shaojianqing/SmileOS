/* 
 * The C function signature of the assembly procedure.The function is to 
 * fetch the data from the equipment port like keyboard and mouse, and in
 * the unit of byte.
 *
 * Parameters:
 * 		port: the port where to fetch the data.
 * Return:
 *		the data in the unit of byte.
 */
u8 inByte(u16 port);

/* 
 * The C function signature of the assembly procedure.The function is to 
 * output the data to the equipment port to set or reset the status of the
 * equipment, like IDE harddisk.
 *
 * Parameters:
 * 		port: the port where to output the data.
 * 	    data: the data to be outputed to the port.
 * Return:
 *		no return value.
 */
void outByte(u16 port, u8 data);

/* 
 * The C function signature of the assembly procedure.The function is to 
 * read a lot of data from the equipment and store the data in the memory
 * buffer, it is now mainly used in reading data block from IDE harddisk.
 *
 * Parameters:
 * 		port: the port where to output the data.
 * 	  buffer: the memory buffer address to receive and store the data.
 *		   n: the size of the data to read from the equipment.
 * Return:
 *		no return value.
 */
void readPort(u16 port, void *buffer, int n);
