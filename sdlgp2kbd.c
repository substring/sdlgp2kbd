#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#include <SDL.h>
#include <linux/uinput.h>

SDL_GameController* sdlgc = NULL;
char* user_gcdb_file = NULL;
int uinput_fd = 0; // should be moved
typedef enum {NOPE = -1, RELEASE = 0, PRESS} press_or_release_type;
typedef enum { LOGLEVEL_NONE, LOGLEVEL_ERROR, LOGLEVEL_WARN, LOGLEVEL_INFO, LOGLEVEL_DEBUG } log_level;
int AXIS_DEAD_ZONE = 8000;
log_level app_log_level = LOGLEVEL_WARN;

void log_error(const char* format, ...)
{
	if(app_log_level < LOGLEVEL_ERROR)
		return;
	va_list args;
	va_start(args, format);
	fprintf(stderr, "ERROR: ");
	vfprintf(stderr, format, args);
	va_end(args);
}

void log_warn(const char* format, ...)
{
	if(app_log_level < LOGLEVEL_WARN)
		return;
	va_list args;
	va_start(args, format);
	fprintf(stderr, "WARN:  ");
	vfprintf(stderr, format, args);
	va_end(args);
}

void log_info(const char* format, ...)
{
	if(app_log_level < LOGLEVEL_INFO)
		return;
	va_list args;
	va_start(args, format);
	printf("INFO:  ");
	vprintf(format, args);
	va_end(args);
}

void log_debug(const char* format, ...)
{
	if(app_log_level < LOGLEVEL_DEBUG)
		return;
	va_list args;
	va_start(args, format);
	fprintf(stderr, "DEBUG: ");
	vfprintf(stderr, format, args);
	va_end(args);
}

void send_input(int fd, int type, int code, int val)
{
	struct input_event ie;

	ie.type = type;
	ie.code = code;
	ie.value = val;
	/* timestamp values below are ignored */
	ie.time.tv_sec = 0;
	ie.time.tv_usec = 0;
	log_debug("Sending fd(%d) type(%d) code(%d) value(%d)\n", fd, type, code, val);

	write(fd, &ie, sizeof(ie));
}

SDL_GameController *findController() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
			log_debug("Found a gamecontroller\n");
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
	SDL_Quit();

	ioctl(uinput_fd, UI_DEV_DESTROY);
	close(uinput_fd);
	exit(0);
}

int init(int argc, char **argv)
{
	struct uinput_setup usetup;

	uinput_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if(uinput_fd == -1)
	{
		log_error("It looks like you don't have write permission to /dev/uinput. Exiting.\n");
		exit(1);
	}

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
	log_debug("Initializing SDL2 GameController system...");
	if(SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
	    log_error("Couldn't initilize SDL!");
		exit(1);
	};
	log_info(" Done!\n");
	sdlgc = findController();
	if(sdlgc == NULL)
	{
		log_error("Failed to find a SDL GameController!");
		deinit(0);
		exit(1);
	}
#if SDL_VERSION_ATLEAST(2,0,2)
	SDL_GameControllerAddMappingsFromFile("/etc/gamecontrollerdb.txt");
	if (user_gcdb_file)
		SDL_GameControllerAddMappingsFromFile(user_gcdb_file);
#elif SDL_VERSION_ATLEAST(3,0,0)
	// Not tested yet
	SDL_AddGamepadMappingsFromFile("/etc/gamecontrollerdb.txt");
	if (user_gcdb_file)
		SDL_AddGamepadMappingsFromFile(user_gcdb_file);
#else
	#error "Please use SDL2 (>= 2.0.2) or SDL3"
#endif
	log_info("There are %d joysticks connected.\n", SDL_NumJoysticks());
	log_info("Controller used is: %s\n", SDL_GameControllerName(sdlgc));
	if (!SDL_IsGameController(0))
	{
		deinit(0);
	}
}

void print_usage()
{
	printf("sdlgp2kbd creates a virtual keyboard and maps gamemapds inputs to that keyboard.\n"
	"This is useful for text based UIs (dialog, ncurses, whiptail, etc...) that require a keyboard.\n"
	"You need your gamepad(s) mapped as as a gamecontroller through a gamecontrollerdb file\n"
	"Mappings are (using a XBOX naming):\n"
	"\tHAT/Left stick: arrow keys\n"
	"\tLeft/Right Shoulder: Page Up/Down\n"
	"\tSTART: Enter\n"
	"\tSELECT: TAB\n"
	"\tA: SPACE\n"
	"\tB: ESC\n"
	"\n"
	"Options:\n"
	"\t-g <file>\tspecify an additionnal gamecontrollerdb file if the system one isn't enough\n"
	"\t-h\t\tprint this help\n"
	"\t-q\t\tquiet mode, no output. Adding -v won't change\n"
	"\t-v\t\tincrease verbosity, can be repeated up to 3 times (-vvv)\n"
	);
}

int main(int argc, char **argv)
{
	int c;
	char *cvalue = NULL;
	log_info("Starting %s...\n", argv[0]);

	// Parse options
	while ((c = getopt (argc, argv, "hvgq:")) != -1)
	switch (c)
	{
		case 'h':
			print_usage();
			exit(0);
			break;
		case 'v':
			if (app_log_level < LOGLEVEL_DEBUG && app_log_level != LOGLEVEL_NONE)
				app_log_level++;
			break;
		case 'g':
			user_gcdb_file = optarg;
			if (access(user_gcdb_file, R_OK) != 0)
			{
				log_error("File %s doesn't exist or can't be read. Aborting!\n", user_gcdb_file);
				exit(1);
			}
			break;
		case 'q':
			app_log_level = LOGLEVEL_NONE;
		case '?':
			if (optopt == 'c')
				log_error("Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				log_error("Unknown option `-%c'.\n", optopt);
			else
				log_error("Unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			log_warn("Unknown option %c\n", c);
			break;
	}



	init(argc, argv);
	
	int quit = SDL_FALSE;
	SDL_Event event;
	int keycode = 0;
	int is_in_dead_zone_Y = 1;
	int was_in_dead_zone_Y = 1;
	int axis_vertical = 0, axis_horizontal = 0;
	press_or_release_type action = NOPE;


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
						log_debug("Pad plugged\n");
						sdlgc = SDL_GameControllerOpen(event.cdevice.which);
					}
					break;

				case SDL_CONTROLLERDEVICEREMOVED:
					log_debug("Pad removed\n");
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
					log_debug("Button pressed!\n");
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
					log_debug("Axis moved (%d) is: ", event.caxis.axis);
					switch (event.caxis.axis)
					{
						case SDL_CONTROLLER_AXIS_LEFTY:
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
						action = NOPE;
					break;

			}
			if (action != NOPE && keycode)
			{
				log_debug("Got an action!\n");
				send_input(uinput_fd, EV_KEY, keycode, action);
				send_input(uinput_fd, EV_SYN, SYN_REPORT, 0);
			}
			action = NOPE;
			keycode = 0;
		}
		if(quit == SDL_TRUE)
			break;
	}
	deinit(0);
}
