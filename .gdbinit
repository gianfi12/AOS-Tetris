target remote :3333
monitor reset halt
monitor flash write_image erase main.bin 0x08000000
monitor reset halt