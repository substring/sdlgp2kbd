CC ?= gcc
LD ?= ld
PKG_CONFIG ?= pkg-config
CFLAGS = -O2
LDFLAGS =

DESTDIR ?=
PREFIX ?= /usr/bin
DATA_DIR ?= /usr/share/controllermap

# Check SDL2 is here
HAS_VALID_SDL2 := $(shell $(PKG_CONFIG) --silence-errors --libs "sdl2 >= 2.0.2"; echo $$?)
ifeq ($(HAS_VALID_SDL2),1)
	$(error You need at least SDL 2.0.2)
endif

CFLAGS  += $(shell $(PKG_CONFIG) --cflags sdl2)
LDFLAGS += $(shell $(PKG_CONFIG) --libs sdl2)

all: sdlgp2kbd controllermap

controllermap:
	$(CC) sdl2-controllermap/controllermap.c sdl2-controllermap/testutils.c -o controllermap -DDATA_DIR=\"$(DATA_DIR)/\" $(CFLAGS) $(LDFLAGS)

sdlgp2kbd:
	$(CC) sdlgp2kbd.c -o sdlgp2kbd $(CFLAGS) $(LDFLAGS)

install-controllermap:
	install -Dm 755 controllermap -t $(DESTDIR)$(PREFIX)
	install -Dm 644 sdl2-controllermap/*.bmp -t $(DESTDIR)$(DATA_DIR)

install:
	install -Dm 755 sdlgp2kbd -t $(DESTDIR)$(PREFIX)

clean:
	rm -f sdlgp2kbd controllermap
