# Using the Apple 1 Emulator

## Overview

The Apple 1 is a 6502 based computer. When the program starts, it creates 64K of
RAM, and then loads the machine's monitor (the BIOS program that runs when the
machine starts) from file file `rom.bin`. This contains 256 bytes(!) of data
loaded into $FF00 through $FFFF. The monitor is an interactive program that
allows you to display memory, enter bytes into memory, and jump to a program.

Unlike a real Apple 1, there are 64K of true RAM. The ROM code technically
should be read-only, but it is editable just like any other RAM. The original
Apple 1 also has limits to available RAM, but essentially any memory address
other than an I/O port can be used as RAM.

When the emulator starts up, you are greeted with a backslash ("\"), a prompt
that the Apple 1 is ready to accept input.

## Accessing Memory

Memory can be examined by typing an address, or a range of addresses. Typing a
single address shows its contents, and typing two addressses separated by a dot
(".") shows a range of memory, e.g.:

```
\

# Print a single location
FFF0

FFF0: 12
FFE0

FFE0: 4A
FFE1

FFE1: 20

# Print a range from start.end, inclusive
FFE0.FFF0

FFE0: 4A 20 E5 FF 68 29 0F 09
FFE8: B0 C9 BA 90 02 69 06 2C
FFF0: 12
```

Memory can be set in the same form that the monitor display it. For example, you
can set a single location in memory with a colon:

```
# Typing 0000: 01 puts $01 in memory location 0
0000: 01

# More than one number can appear on a line, so this puts $10 in $0010, $11 in
# $0011. and $12 in $0012
0010: 10 11 12
```

You can jump to a program by typing an address, followed by R, e.g., `300R`.

## Loading and Saving Programs

The terminal is the best way to get software into and out of the emulator. For
example, the file [fig6502.mon](fig6502.mon) is a machine monitor dump of a
program, the Fig-Forth programming language, and [tinybasic.mon](tinybasic.mon)
is an implementation of Tiny BASIC. This is a text file with a binary dump of
the program, followed by a command to run the program. This can be simply copied
and pasted into the machine language monitor, which will load (and run) the
program.

Similarly, programs aren't saved, but you can paste the contents of the terminal
into a text file. Since the monitor can emit the contents of RAM, you can
display a block of RAM, save it to a text file, and then load it later.

## Quitting the Emulator

To exit the emulator, hit the pipe (vertical bar, "|") key.
