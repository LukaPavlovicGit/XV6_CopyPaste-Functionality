# xv6 Operating System


## [video demonstration](domaci1-demo.mp4)

## [project specification](OS-Domaći1.pdf)

## Adding copy-paste support in the Xv6 terminal

To support the copy-paste functionality, I've added the following functionalities:
1. 	Entry in copy-paste mode.	
2.	Text Selection and copying.
3. 	Text paste.

To start the program, follow the steps below:

1. Open the terminal in project's directory
2. Call command ***'make clean'***
3. Then call command ***'make qemu'***

The xv6 operating system should start at this point and the QEMU window should be displayed

4. press ***SHIFT + ALT + C*** to copy-paste mode
5. use ***W, A, S or D*** keys to navigate the cursor
6. press ***Q*** to start with selection mode, then use the navigation keys from 5. to select the text to be copied
7. when text is selected press ***E*** to exit selection mode
8. press ***SHIFT + ALT + C*** to exit copy mode

When exiting copy mode, the cursor returns to the position on the screen from which copy mode was started.

9. press ***SHIFT + ALT + P*** to paste the copied text

When copy mode is enabled, the text over which the cursor passes is colored black on white (as opposed to the original text) during cursor navigation and text selection.
