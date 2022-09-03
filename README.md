# xv6 Operating System - assignment 1
## Adding copy-paste functionality - [full specification](https://drive.google.com/drive/u/2/folders/1JUCaBy4ctjTKPeo5Uaq3t7NCrKcvzL-b)

Xv6 modified to support copy-paste functionality. This project is supposed to work on Linux machine (virtual machine could be handy tool).

To start program follow next steps:

1. Open the terminal in the directory of the project
2. Call command 'make clean'
3. Then call command 'make qemu'

The xv6 operating system should be started at this point, and QEMU window should be displayed

4. press **shift + alt + c** simultaneously to start copy mode
5. use **w, a, s or d** keys to navigate the cursor
6. press **q** to start with selection mode, then use navigation keys from 5. to select text to be copied
7. when text is selected press **e** to exit selection mode
8. press **shift + alt + c** simultaneously to exit copy mode
9. press **shift + alt + p** simultaneously to paste the copied text

In the copy mode, during cursor navigation and text selection, text over which the cursor passes is colored black-on-white (opposite than the original text).
When exiting the copy mode, cursor will return on the position on the screen where the copy mode has been started.