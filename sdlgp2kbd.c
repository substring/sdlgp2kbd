#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#include <SDL.h>
#include <linux/uinput.h>

SDL_GameController* sdlgc = NULL;
int uinput_fd = 0; // should be moved
typedef enum {BLAH = -1, RELEASE = 0, PRESS} press_or_release_type;
int AXIS_DEAD_ZONE = 8000;

void send_input(int fd, int type, int code, int val)
{
	struct input_event ie;

	ie.type = type;
	ie.code = code;
	ie.value = val;
	/* timestamp values below are ignored */
	ie.time.tv_sec = 0;
	ie.time.tv_usec = 0;
	printf("Sending fd(%d) type(%d) code(%d) value(%d)\n", fd, type, code, val);

	write(fd, &ie, sizeof(ie));
}

SDL_GameController *findController() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
			printf("Found a gamecontroller\n");
            return SDL_GameControllerOpen(i);
        }
    }

    return NULL;
}

SDL_JoystickID getControllerInstanceID(SDL_GameController *controller)
{
    return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
}


void deinit(int s)
{
	printf("\n%s caught, cleaning up & quitting.\n", 
		   s==SIGINT ? "SIGINT" : 
		   (s==SIGTERM ? "SIGTERM" : ((s == 0) ? "Window die" : "Unknown")));
	SDL_Quit();

	ioctl(uinput_fd, UI_DEV_DESTROY);
	close(uinput_fd);
	exit(0);
}

int init(int argc, char **argv)
{
	struct uinput_setup usetup;

	uinput_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

	/*
	* The ioctls below will enable the device that is about to be
	* created, to pass key events, in this case the space key.
	*/
	ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_SPACE);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_ENTER);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_TAB);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_ESC);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_UP);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_DOWN);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_LEFT);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_RIGHT);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_PAGEUP);
	ioctl(uinput_fd, UI_SET_KEYBIT, KEY_PAGEDOWN);

	memset(&usetup, 0, sizeof(usetup));
	usetup.id.bustype = BUS_USB;
	usetup.id.vendor = 0x15D9;  /* sample vendor */
	usetup.id.product = 0x0A37; /* sample product */
	strcpy(usetup.name, "SDL GameController Keyboard");

	ioctl(uinput_fd, UI_DEV_SETUP, &usetup);
	ioctl(uinput_fd, UI_DEV_CREATE);

	/* Go for the SDL2 part */
	//~ if(SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	printf("Initializing SDL2 GameController system...");
	if(SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
	    puts("Couldn't initilize SDL!");
		exit(1);
	};
	printf(" Done!\n");
	sdlgc = findController();
	if(sdlgc == NULL)
	{
		puts("Failed to find a SDL GameController!");
		deinit(0);
		exit(1);
	}
#if SDL_VERSION_ATLEAST(2,0,2)
	SDL_GameControllerAddMappingsFromFile("/etc/gamecontrollerdb.txt");
#elif SDL_VERSION_ATLEAST(3,0,0)
	SDL_AddGamepadMappingsFromFile("/etc/gamecontrollerdb.txt");
#else
	#error "Please use SDL2 or SDL3"
#endif
	printf("There are %d joysticks connected.\n", SDL_NumJoysticks());
	printf("Controller used is: %s\n", SDL_GameControllerName(sdlgc));
	if (!SDL_IsGameController(0))
	{
		deinit(0);
	}
}


int main(int argc, char **argv)
{
	printf("Starting...\n");
	init(argc, argv);
	
	int quit = SDL_FALSE;
	SDL_Event event;
	int keycode = 0;
	int is_in_dead_zone_Y = 1;
	int was_in_dead_zone_Y = 1;
	int axis_vertical = 0, axis_horizontal = 0;
	press_or_release_type action = BLAH;


	while (quit == SDL_FALSE)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;

				case SDL_CONTROLLERDEVICEADDED:
					if (!sdlgc)
					{
						printf("Pad plugged\n");
						sdlgc = SDL_GameControllerOpen(event.cdevice.which);
					}
					break;

				case SDL_CONTROLLERDEVICEREMOVED:
					printf("Pad removed\n");
					if (sdlgc && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(sdlgc))) 
					{
						SDL_GameControllerClose(sdlgc);
						sdlgc = findController();
					}
					break;

				case SDL_CONTROLLERBUTTONUP:
				case SDL_CONTROLLERBUTTONDOWN:
					if (event.type == SDL_CONTROLLERBUTTONUP)
						action = RELEASE;
					if (event.type == SDL_CONTROLLERBUTTONDOWN)
						action = PRESS;
					
					if (sdlgc && event.cdevice.which != getControllerInstanceID(sdlgc))
						break;
					printf("Button pressed!\n");
					switch (event.cbutton.button) 
					{
						case SDL_CONTROLLER_BUTTON_A:
							keycode =  KEY_SPACE;
							break;
						case SDL_CONTROLLER_BUTTON_B:
							keycode = KEY_ESC;
							break;
						case SDL_CONTROLLER_BUTTON_START:
							keycode = KEY_ENTER;
							break;
						case SDL_CONTROLLER_BUTTON_BACK:
							keycode = KEY_TAB;
							break;
						case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
							keycode = KEY_PAGEUP;
							break;
						case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
							keycode = KEY_DOWN;
							break;

						case SDL_CONTROLLER_BUTTON_DPAD_UP:
							keycode = KEY_UP;
							break;
						case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
							keycode = KEY_DOWN;
							break;
						case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
							keycode = KEY_LEFT;
							break;
						case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
							keycode = KEY_RIGHT;
							break;
					}
					break;

				case SDL_CONTROLLERAXISMOTION:
					if (sdlgc && event.caxis.which != getControllerInstanceID(sdlgc))
						break;
					//~ printf("Axis moved (%d) is: ", event.caxis.axis);
					switch (event.caxis.axis)
					{
						case SDL_CONTROLLER_AXIS_LEFTY:
							//~ printf("LEFTY\n");
							was_in_dead_zone_Y = is_in_dead_zone_Y;
							is_in_dead_zone_Y = (abs(event.caxis.value) > AXIS_DEAD_ZONE) ? 0 : 1;
							keycode = event.caxis.value > 0 ? KEY_DOWN : KEY_UP;
							break;
							
					}
					// Decide if we fire an event
					if (was_in_dead_zone_Y && !is_in_dead_zone_Y)
						action = PRESS;
					else if (!was_in_dead_zone_Y && is_in_dead_zone_Y)
						action = RELEASE;
					else
						action = BLAH;
					break;

			}
			if (action != BLAH && keycode)
			{
				printf("Got an action!\n");
				send_input(uinput_fd, EV_KEY, keycode, action);
				send_input(uinput_fd, EV_SYN, SYN_REPORT, 0);
			}
			action = BLAH;
			keycode = 0;
		}
		if(quit == SDL_TRUE)
			break;
	}
	deinit(0);
}
