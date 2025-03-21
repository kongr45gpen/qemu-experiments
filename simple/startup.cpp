// stack definition code

// top of stack
extern unsigned __stacktop;

// initial stack pointer is first address of program
__attribute__((section(".stack"), used)) unsigned *__stack_init = &__stacktop;

// very simple startup code with definition of handlers for all cortex-m cores

typedef void (*ptr_func_t)();

// main application
extern int main();

// location of these variables is defined in linker script
extern unsigned __data_start;
extern unsigned __data_end;
extern unsigned __data_load;

extern unsigned __bss_start;
extern unsigned __bss_end;

extern unsigned __heap_start;

extern ptr_func_t __preinit_array_start[];
extern ptr_func_t __preinit_array_end[];

extern ptr_func_t __init_array_start[];
extern ptr_func_t __init_array_end[];

extern ptr_func_t __fini_array_start[];
extern ptr_func_t __fini_array_end[];

/**
 * Handlers setup code for Cortex-M.
 */

 typedef void (*ptr_func_t)();

 // Undefined handler is pointing to this function, this stop MCU.
 // This function name must by not mangled, so must be C,
 // because alias("..") is working only with C code
 extern "C" void __stop() { while (true); }
 
 // Handlers for Cortex-M core.
 // These handler are with attribute 'weak' and can be overwritten
 // by non-week function, default is __stop() function
 extern "C" void Reset_Handler();
 __attribute__((weak, alias("__stop"))) void NMI_handler();
 __attribute__((weak, alias("__stop"))) void HARDFAULT_handler();
 __attribute__((weak, alias("__stop"))) void MEMMANAGE_handler();
 __attribute__((weak, alias("__stop"))) void BUSFAULT_handler();
 __attribute__((weak, alias("__stop"))) void USAGEFAULT_handler();
 __attribute__((weak, alias("__stop"))) void SVCALL_handler();
 __attribute__((weak, alias("__stop"))) void DEBUGMONITOR_handler();
 __attribute__((weak, alias("__stop"))) void PENDSV_handler();
 __attribute__((weak, alias("__stop"))) void SYSTICK_handler();
 
 // Dummy handler (for unused vectors)
 __attribute__((weak, alias("__stop"))) void DUMMY_handler();
 
 // Vector table for handlers
 // This array will be placed in ".vectors" section defined in linker script.
 __attribute__((section(".vectors"), used)) ptr_func_t __isr_vectors[] = {
     Reset_Handler,
     NMI_handler,
     HARDFAULT_handler,
     MEMMANAGE_handler,
     BUSFAULT_handler,
     USAGEFAULT_handler,
     DUMMY_handler,
     DUMMY_handler,
     DUMMY_handler,
     DUMMY_handler,
     SVCALL_handler,
     DEBUGMONITOR_handler,
     DUMMY_handler,
     PENDSV_handler,
     SYSTICK_handler,
 };


/** Copy default data to DATA section
 */
void copy_data() {
    unsigned *src = &__data_load;
    unsigned *dst = &__data_start;
    while (dst < &__data_end) {
        *dst++ = *src++;
    }
}

/** Erase BSS section
 */
void zero_bss() {
    unsigned *dst = &__bss_start;
    while (dst < &__bss_end) {
        *dst++ = 0;
    }
}

/** Fill heap memory
 */
void fill_heap(unsigned fill=0x45455246) {
    unsigned *dst = &__heap_start;
    unsigned *msp_reg;
    __asm__("mrs %0, msp\n" : "=r" (msp_reg) );
    while (dst < msp_reg) {
        *dst++ = fill;
    }
}

/** Call constructors for static objects
 */
void call_init_array() {
    auto array = __preinit_array_start;
    while (array < __preinit_array_end) {
        (*array)();
        array++;
    }

    array = __init_array_start;
    while (array < __init_array_end) {
        (*array)();
        array++;
    }
}

/** Call destructors for static objects
 */
void call_fini_array() {
    auto array = __fini_array_start;
    while (array < __fini_array_end) {
        (*array)();
        array++;
    }
}

// reset handler
extern "C" void Reset_Handler() {
    copy_data();
    zero_bss();
    fill_heap();
    call_init_array();
    // run application
    main();
    // call destructors for static instances
    call_fini_array();
    // stop
    while (true);
}