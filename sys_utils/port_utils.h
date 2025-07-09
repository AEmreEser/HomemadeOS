#ifndef _PORT_UTILS_H_
#define _PORT_UTILS_H_

// MEMORY MAPPED PORT UTILITY FUNCS

//** READ
// PORTSIZE 8 bits
unsigned char volatile inline read_byte(const unsigned int port)  {
    unsigned char result;
    __asm__ volatile("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

// PORTSIZE 16 bits
unsigned short volatile inline read_word(const unsigned int port)  {
    unsigned short result;
    __asm__ volatile("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

// PORTSIZE 32 bits
unsigned int volatile inline read_dbl_word(const unsigned int port)  {
    unsigned int result;
    __asm__ volatile("in %%dx, %%eax" : "=a" (result) : "d" (port));
    return result;
}


//**WRITE
// PORTSIZE 8 bits
void volatile inline write_byte(const unsigned int port, const unsigned char data)  {
    __asm__ volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}

// PORTSIZE 16 bits
void volatile inline write_word(const unsigned int port, const unsigned short data)  {
    __asm__ volatile("out %%ax, %%dx" : : "a" (data), "d" (port));
}

// PORTSIZE 32 bits
void volatile inline write_dbl_word(const unsigned int port, const unsigned int data)  {
    __asm__ volatile("out %%eax, %%dx" : : "a" (data), "d" (port));
}

#endif
