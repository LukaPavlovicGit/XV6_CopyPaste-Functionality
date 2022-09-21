# xv6 Operating System
## Adding copy-paste functionality in the terminal

Xv6 modified to support copy-paste functionality. This project is supposed to work on Linux machine (virtual machine could be handy tool).

To support copy-paste functionality i've added the following functionalities:
1. 	Entry in the copy mode.
	
	
2.	Text Selection and copying.

3. 	Text paste.

To start program follow next steps:

1. Open the terminal in project's directory
2. Call command ***'make clean'***
3. Then call command ***'make qemu'***

The xv6 operating system should be started at this point, and QEMU window should be displayed

4. press ***SHIFT + ALT + C*** to start copy mode
5. use ***W, A, S or D*** keys to navigate the cursor
6. press ***Q*** to start with selection mode, then use navigation keys from 5. to select the text to be copied
7. when text is selected press ***E*** to exit selection mode
8. press ***SHIFT + ALT + C*** to exit copy mode

When exiting the copy mode, cursor will return on the position on the screen from where the copy mode has been started.

9. press ***SHIFT + ALT + P*** to paste the copied text

During cursor navigation and text selection, when the copy mode is on, text over which the cursor passes is colored black-on-white (opposite than the original text).