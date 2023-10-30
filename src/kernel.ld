ENTRY(_kernel_main)

SECTIONS {
	/* load kernel at 1MiB */
    . = 1M;

	.boot : {
        *(.multiboot)
	}

    .text : {
        *(.text)
    }

  	.rodata : {
  		*(.rodata)
  	}

    .data : {
    	*(.data)
    }

    .bss : {
		*(.bss)
		*(COMMON)
    }

    /DISCARD/ : {
    	*(.eh_frame)
        *(.comment)
    }
}