#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef struct {
    // those pushed first will be first here
    uint32_t ds, es, fs, gs;
    uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax; // pusha
    uint32_t intr_number, error_code;
    uint32_t eip, cs, eflags, user_esp, ss; // interrupt call pushes these

} int_stack_frame_t; // a snapshot of the stack during an isr execution

#endif