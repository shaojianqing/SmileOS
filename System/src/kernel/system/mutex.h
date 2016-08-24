
#define STATUS_LOCK			TRUE
#define STATUS_UNLOCK		FALSE
k
/* The data structure of the mutex, containing the lock/unlock
 * status and the process pointer the mutex controls. 
 */
typedef struct Mutex 
{
	Process *process;

	bool status;

} Mutex;

/* Initialize the particiular mutex.Once one mutex is created, 
 * calling this funcation is just to initialize the mutex and 
 * set the default value and status.
 *
 * Parameters:
 * 		mutex: The mutex to be initialized.
 */
void initMutex(Mutex *mutex);

/* Perform the lock operation on the particiular mutex.
 *
 * Parameters:
 * 		mutex: The mutex to be locked.
 */
void lockMutex(Mutex *mutex);

/* Perform the unlock operation on the particiular mutex.
 *
 * Parameters:
 * 		mutex: The mutex to be unlocked.
 */
void unlockMutex(Mutex *mutex);
