CC ?= gcc
LD ?= ld
PKG_CONFIG ?= pkg-config
CFLAGS =
LDFLAGS =

# Check SDL2 is here
HAS_VALID_SDL2 := $(shell $(PKG_CONFIG) --silence-errors --libs "sdl2 >= 2.0.2"; echo $$?)
ifeq ($(HAS_VALID_SDL2),1)
	$(error You need at least SDL 2.0.2)
endif

CFLAGS  += $(shell $(PKG_CONFIG) --cflags sdl2)
LDFLAGS += $(shell $(PKG_CONFIG) --libs sdl2)

sdlgp2kbd:
	$(CC) sdlgp2kbd.c -o sdlgp2kbd $(CFLAGS) $(LDFLAGS)

all: sdlgp2kbd

install:
	install -Dm 755 sdlgp2kbd -t /usr/bin

clean:
	rm sdlgp2kbd
