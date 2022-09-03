# xv6 Operating System - assignment 1
## Adding copy-paste functionality - full specification in the [link](https://drive.google.com/drive/u/2/folders/1JUCaBy4ctjTKPeo5Uaq3t7NCrKcvzL-b)

Xv6 modified to support copy-paste functionality. This project is supposed to work on Linux machine (virtual machine could be handy tool).

To start program follow next steps:

1. Open the terminal in project's directory
2. Call command ***'make clean'***
3. Then call command ***'make qemu'***

The xv6 operating system should be started at this point, and QEMU window should be displayed

4. press ***SHIFT + ALT + C*** simultaneously to start copy mode
5. use ***W, A, S or D*** keys to navigate the cursor
6. press ***Q*** to start with selection mode, then use navigation keys from 5. to select text to be copied
7. when text is selected press ***E*** to exit selection mode
8. press ***SHIFT + ALT + C*** simultaneously to exit copy mode
9. press ***SHIFT + ALT + P*** simultaneously to paste the copied text

During cursor navigation and text selection, in the copy mode, text over which the cursor passes is colored black-on-white (opposite than the original text).

When exiting the copy mode, cursor will return on the position on the screen from where the copy mode has been started.