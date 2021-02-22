# Tetris project for the course of AOS

This the repository used for the development of the Tetris project, associated to the course of AOS at the Polimi.

## Installation usage
Follow this [guide](https://miosix.org/wiki/index.php?title=Linux_Quick_Start) to install correctly the board.
Clone the repository of [Miosix](https://github.com/fedetft/miosix-kernel).
Copy this repository inside the miosix-kernel/ path. Substitute the main.cpp file with this one and use the command
>make
to compile the executable.
## OPENOCD configuration
After installing the driver for your target device use Openocd to open a connection with it by typing 
>openocd -f stm32l4nucleo.cfg 
In this repository is already present the configuration file needed to launch Openocd on the STM32 NUCLEO-L476RG.

## Debug
For debugging purposes modify the file [.gdbinit](.gdbinit), and then launch gdb with
>arm-miosix-eabi-gdb main.elf --command=.gdbinit

## Access the board output
In order to access what the board prints on screen you should use
>screen /dev/ttyACM0 19200
then you can exit by pressing Ctrl+A -> k -> y.