#include <unistd.h>
#include <sys/mman.h>

#define MEMSIZE 4096
#define MINBUFSIZE 8
#define BITMAPSIZE MEMSIZE/MINBUFSIZE

/**
 * @brief initialises the data structure
 * for the memory manager application
 * 
 * @return int : success/failure status
 */
int init();

/**
 * @brief releases all memory to OS
 * and performs other cleanup task
 * 
 * @return int : success/failure status
 */
int cleanup();

/**
* @param size The size of req. membuf
*
* @return char * : Memory location to allocated buf
*/
char *alloc(int size);

/**
 * @brief Deallocates the memory location
 * pointed to by buf
 * 
 * @param buf pointer to buffer in mem
 */
void dealloc(char *buf);