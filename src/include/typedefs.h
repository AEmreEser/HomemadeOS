#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// SHOULD THIS NOT BE PACKED???
// THE ORDER OF THESE MUST BE CHECKED!!!
// typedef struct {
//     // those pushed first will be first here
//     uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax; // pusha
//     uint32_t gs, fs, es, ds; // reverse order of pushing
//     uint32_t eip, cs, eflags, user_esp, ss; // interrupt call pushes these
//     uint32_t intr_number, error_code; // the error codes and intr numbers we pushed manually

// } int_stack_frame_t; // a snapshot of the stack during an isr execution

typedef struct {
    // pushed manually (check isr_irq_routines.asm): 
    uint32_t gs, fs, es, ds;
    // pushed by pusha:
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t intr_number;
    uint32_t error_code;
    uint32_t eip, cs, eflags, user_esp, ss;
} __attribute__((packed)) int_stack_frame_t;


#endif