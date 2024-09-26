# sdlgp2kbd
Convert GamePad inputs to keyboard inputs. Useful for text only UIs (ncurses etc...). Simulates keyboard inputs such as arrows, ENTER, TAB, ESC, Page Up/Down. This is done using SDL to capture GamePad events through the universal GameController API, and create a keyboard device using uinput

# Requirements
- SDL2
- Kernel headers
- /etc/gamecontrollerdb.txt

# Build
```
gcc sdlgp2kbd.c -o sdlgp2kbd $(pkg-config --cflags sdl2) -lSDL2
```

# Run
You can run it by several means, all of them require your user to have write access to /dev/uinput.

Root, of course, can use it flawlessly. Not necessarily the recommended way of using it.

It can also be done as a user if you set the proper owner/group to /dev/uinput and of course that user belonging to that specific group. If you want this to survive after a reboot, you should add a udev rule + load the uinput module at boot to trigger the rule.

# TODO
- Add a makefile
- SDL3 support
- command line argument for XBOX/SNES layout
- ~~command line argument for gamecontrollerdb.txt path~~
- gamecontroller index / ~~all existing gamecontrollers~~
- map gamecontroller buttons to keys
- exclusive access to gamepads to prevent double inputs

# Source
https://www.kernel.org/doc/html/v6.10/input/uinput.html
