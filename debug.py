import argparse
from pwn import *
import sys
import signal

# Setup a signal handler when you want to exit debug mode
def signal_handler(sig, frame):
    print('You pressed Ctrl+C!')
    r.kill()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

# Setup the launched terminal. You have to install the Terminator terminal if you want to use it with:
# $ sudo apt-get install terminator
# In order for a better debug use https://github.com/pwndbg/pwndbg
# The usage of gdb.attach() requires to execute the following line:
# $ echo 0 > /proc/sys/kernel/yama/ptrace_scope
context.terminal = ["terminator", "-e"]

# Make the program if requested
parser = argparse.ArgumentParser()
parser.add_argument("--compile", help="compile the program",
                    action="store_true")
args = parser.parse_args()
if args.compile:
    print("Compiling the program:")
    r = process("make",shell=True)
    makeOutput = r.recvall().decode("utf-8")
    r.wait_for_close()

    if "error" in makeOutput:
        print(makeOutput)
        sys.exit("Cannot compile")

# Start the debug process.
r = process("arm-miosix-eabi-gdb main.elf",shell=True)
print(r.recvuntil("(gdb) ").decode("utf-8"))
r.sendline("target remote :3333")
print(r.recvuntil("(gdb) ").decode("utf-8"))
r.sendline("monitor reset halt")
print(r.recvuntil("(gdb) ").decode("utf-8"))
r.sendline("monitor flash write_image erase main.bin 0x08000000")
print(r.recvuntil("(gdb) ").decode("utf-8"))
r.sendline("monitor reset halt")
print(r.recvuntil("(gdb) ").decode("utf-8"))

r.interactive()
