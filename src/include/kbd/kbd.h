#ifndef _H_KBD_
#define _H_KBD_

extern uint8_t modifier_key_status;
extern unsigned char kbdus[128];

void keyboard_int_handler(int_stack_frame_t * sf);

void install_kbd_irq(void);

#endif