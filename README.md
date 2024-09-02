# sdlgp2kbd
Convert GamePad inputs to keyboard inputs. Useful for text only UIs (ncurses etc...). Simulates keyboard inputs such as arrows, ENTER, TAB, ESC, Page Up/Down

# Requirements
Requires /etc/gamecontrollerdb.txt

# Build
gcc sdlgp2k.c -o sdlgp2k -DENABLE_CONSOLE $(pkg-config --cflags sdl2) -lSDL2

# TODO
- Add a makefile
- SDL3 support
- command line argument for XBOX/SNES layout
- command line argument for gamecontrollerdb.txt path
- gamecontroller index / all existing gamecontrollers
- map gamecontroller buttons to keys

# Source
https://www.kernel.org/doc/html/v6.10/input/uinput.html
