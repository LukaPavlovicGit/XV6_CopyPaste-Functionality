# [video demonstration](https://drive.google.com/file/d/1W80GeFmxveAfJZDpjegqjH1-Ki-OzZiL/view?usp=drive_link)

# [project specification](OS-Domaći1.pdf)

# Copy-Paste Support in XV6 Operating System Terminal

## Overview
I've implemented copy-paste functionality in the terminal with three main features:
1. Ability to enter copy-paste mode
2. Text selection and copying
3. Pasting text

## Getting Started
First, make sure to:
1. Open your terminal in the project's directory
2. Run `make clean`
3. Run `make qemu`

At this point, the XV6 operating system should launch and display the QEMU window.

## Using Copy-Paste
Here's how to use the copy-paste features:

### Basic Controls
1. **Enter Copy Mode**: Press `Shift + Alt + C`
2. **Navigate**: Use `W`, `A`, `S`, or `D` keys to move your cursor around
3. **Select Text**: 
   - Press `V` to begin selecting text
   - Use the navigation keys to highlight what you want to copy
   - Press `E` when you're done selecting
4. **Exit Copy Mode**: Press `Shift + Alt + C` again
   - Your cursor will return to where you started
5. **Paste**: Press `Shift + Alt + P` to paste your copied text

### Note
While in copy mode, text under your cursor will appear highlighted (black on white background) to make navigation and selection easier.
