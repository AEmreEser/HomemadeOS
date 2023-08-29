#define CL_GREEN_ON_BLACK 0x02
#define VID_MEM_PTR 0xb8000

/* 
VIDEO MEMORY ORGANIZATION: 16 bits per letter: low nibble char, high nibble attribute/formatting info
*/

/*
IMPORTANT: the bootloader will blindly begin executing the compiled code from bottom up, hence any function DEFINITION placed here are likely to be executed before main
*/

// STR should be zero terminated
volatile void print_str(const volatile char const * str){

    volatile char ch_iter = *(str);
    volatile char i = (char) (0);

    while (ch_iter != '\0'){
        *((volatile char *) (VID_MEM_PTR + i * 2)) = ch_iter;
        *((volatile char *) (VID_MEM_PTR + i * 2 + 1)) = CL_GREEN_ON_BLACK; 
        i++;
        ch_iter = *(str + i * sizeof(char));
    }

}


void kmain(){
    const volatile char const * test_str = "This is a test!\0";
    volatile char * vid_mem = (volatile char *) (0xb8000);

    print_str(test_str);
}
