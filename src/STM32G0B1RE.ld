ENTRY(Reset_Handler)

MEMORY {
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 512K   
    SRAM  (xrw)     : ORIGIN = 0x20000000, LENGTH = 144K
}

SECTIONS {
    .isr_vector : {
        KEEP(*(.isr_vector))
    } >FLASH

    .text : {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    .init_array : {
        . = ALIGN(4);
        __init_array_start = .;
        KEEP(*(.init_array*))
        __init_array_end = .;
        . = ALIGN(4);
    } >FLASH

    _sidata = LOADADDR(.data);

    .data : {
        . = ALIGN(4);
        _data_start = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } >SRAM AT> FLASH

    .bss : {
        . = ALIGN(4);
        _bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _bss_end = .;
    } >SRAM

     ._user_heap_stack : {
        . = ALIGN(4);
        PROVIDE (_heap_start = .);
        _end = . ;
    } >SRAM

    _estack = ORIGIN(SRAM) + LENGTH(SRAM);
}