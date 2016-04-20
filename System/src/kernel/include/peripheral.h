/* 
 * Initialize the preripheral status, so that the preripheral can be ready to trigger interrupt
 * and respond to the user. This procedure contains the timer, keyboard and mouse initialization.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initPeripheralStatus();

/* 
 * Initialize the system queue buffer, so that the interrupt process handlers can accept and store
 * the data from the preripheral into the system buffer.
 *
 * Parameters:
 * 		no parameters.
 * Return:
 *		no return value.
 */
void initQueueBufferData();
