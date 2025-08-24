MEMORY
{
  flash (rx) : ORIGIN = 0x10000000, LENGTH = 2048K 
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

STACK_SIZE = 0x2000;

ENTRY(_entry_point)

SECTIONS
{
  .flash_begin : {
    __flash_binary_start = .;
  } > flash

  .boot2 : {
    __boot2_start__ = .;
    KEEP(*(.boot2*))
    __boot2_end__ = .;
  } > flash

  ASSERT(__boot2_end__ - __boot2_start__ == 256,
    "ERROR: Pico second stage bootloader must be 256 bytes in size")

  .vector : {
    KEEP(*(.vector*))
    . = ALIGN(0x100);
  } > flash

  .text 0x10000200 : {
    _entry_point = .;
    *(.reset_handler)
    *(.text*)
    *(.rodata*)
    _etext = .;
    . = ALIGN(0x100);
  } > flash

  .data : {
    _sdata = .;
    *(.data*)
    _edata = .;
    . = ALIGN(0x100);
  } > flash

  .bss (NOLOAD) : {
    __bss_start__ = .;
    *(.bss*)    
    *(COMMON)
    __bss_end__ = .;
  } > ram

  .stack (NOLOAD) : {
    . = ALIGN(0x8);
    . = . + STACK_SIZE;
    . = ALIGN(0x8);
    _estack = .;
  } > ram

  _end = .;
}
