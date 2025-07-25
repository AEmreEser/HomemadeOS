#include "include/typedefs.h"
#include "include/utils/vga_utils.h"
#include "include/utils/system_utils.h"
#include "include/isr_irq/irq.h"
#include "include/kbd/kbd.h"

uint8_t modifier_key_status = 0x00; // left shift || right shift || control || alt || caps lock
extern offset_t offset;

#define L_SH_MASK 0x80;
#define R_SH_MASK 0x40;
#define CTRL_MASK 0x20;
#define ALT_MASK  0x10;
#define CAPS_MASK 0x08;

#define SC_CTRL (29)
#define SC_LSH  (42)
#define SC_RSH  (54)
#define SC_ALT  (56)

// taken from Brandon's tutorial
unsigned char kbdus[128] = {
    0, /* esc??? */ 27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   
    0,		/* Left shift (42) */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   
    0,				/* Right shift (54) */
  '*',
    0,	/* Alt (56) */
  ' ',	/* Space bar */
    0,	/* Caps lock (58) */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

// taken from Brandon's tutorial
void keyboard_int_handler(int_stack_frame_t * sf) {
    unsigned char scancode;
    scancode = inportb(0x60);

    offset = print_str("kbd interrupt!! = ", CL_GREEN_ON_BLACK, offset);
    offset = print_num((uint8_t) scancode, CL_WHITE_ON_BLACK, offset);
    offset = print_single_chr('\n', CL_GREEN_ON_BLACK, offset);

    /* Read from the keyboard's data buffer */

    if (scancode & 0x80) { // release
        if (scancode == SC_CTRL){
            modifier_key_status &= ~CTRL_MASK;

        } else if (scancode == SC_LSH) {
            modifier_key_status &= ~L_SH_MASK;

        } else if (scancode == SC_RSH) {
            modifier_key_status &= ~R_SH_MASK;

        } else if (scancode == SC_ALT) {
            modifier_key_status &= ~ALT_MASK;
        }

    } else { // press
        if (scancode == SC_CTRL){
            modifier_key_status |= CTRL_MASK;

        } else if (scancode == SC_LSH) {
            modifier_key_status |= L_SH_MASK;

        } else if (scancode == SC_RSH) {
            modifier_key_status |= R_SH_MASK;

        } else if (scancode == SC_ALT) {
            modifier_key_status |= ALT_MASK;

        } else { // TODO: THIS PRINTS THE CODE, NOT THE CHARACTER -- WHY? I DO NOT KNOW
            offset = print_single_chr(kbdus[scancode], CL_WHITE_ON_BLACK, offset);
        }

    }
}

void install_kbd_irq(void){
    install_single_irq(1, keyboard_int_handler);
}
