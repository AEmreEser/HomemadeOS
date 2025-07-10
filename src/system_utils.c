#include "include/utils/system_utils.h"

// returns dest if copy successful, returns NULL if unsuccessful
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	if (dest == NULL || src == NULL){ return NULL; }

	for (int i = 0; i < count; i++){
		dest[i] = src[i];
	}
	return dest;
}

// returns dest if copy successful, returns NULL if unsuccessful
unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
	if (dest == NULL){ return NULL; }

	for (int i = 0; i < count; i++){
		dest[i] = val;
	}
	return dest;
}

// returns dest if copy successful, returns NULL if unsuccessful
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
	if (dest == NULL){ return NULL; }

	for (int i = 0; i < count; i++){
		dest[i] = val;
	}
	return dest;
}

// returns -1 if str unitialized
int strlen(const char *str)
{
	if (str == NULL) { return -1; }

	int i = 0;
	while(str[i] != '\0') { i++; }

	return i;
}

// taken from Brandon F. 
/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

// taken from Brandon F. 
/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

	