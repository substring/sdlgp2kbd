#include <string.h>
#include <linux/input-event-codes.h>

#define MIN_EVENT_VALUE 1
#define MAX_EVENT_VALUE 111

int get_event_value_from_name(const char* event_name)
{
  /* If it's a valid digit, use it */
  int int_value = atoi(event_name);
  if(int_value != 0)
    if(int_value >= MIN_EVENT_VALUE && int_value <= MAX_EVENT_VALUE)
    {
      return int_value;
    }
    else
      return 0;

	if (strcmp(event_name, "KEY_ESC") == 0) return KEY_ESC ;
	if (strcmp(event_name, "KEY_1") == 0) return KEY_1 ;
	if (strcmp(event_name, "KEY_2") == 0) return KEY_2 ;
	if (strcmp(event_name, "KEY_3") == 0) return KEY_3 ;
	if (strcmp(event_name, "KEY_4") == 0) return KEY_4 ;
	if (strcmp(event_name, "KEY_5") == 0) return KEY_5 ;
	if (strcmp(event_name, "KEY_6") == 0) return KEY_6 ;
	if (strcmp(event_name, "KEY_7") == 0) return KEY_7 ;
	if (strcmp(event_name, "KEY_8") == 0) return KEY_8 ;
	if (strcmp(event_name, "KEY_9") == 0) return KEY_9 ;
	if (strcmp(event_name, "KEY_0") == 0) return KEY_0 ;
	if (strcmp(event_name, "KEY_MINUS") == 0) return KEY_MINUS ;
	if (strcmp(event_name, "KEY_EQUAL") == 0) return KEY_EQUAL ;
	if (strcmp(event_name, "KEY_BACKSPACE") == 0) return KEY_BACKSPACE ;
	if (strcmp(event_name, "KEY_TAB") == 0) return KEY_TAB ;
	if (strcmp(event_name, "KEY_Q") == 0) return KEY_Q ;
	if (strcmp(event_name, "KEY_W") == 0) return KEY_W ;
	if (strcmp(event_name, "KEY_E") == 0) return KEY_E ;
	if (strcmp(event_name, "KEY_R") == 0) return KEY_R ;
	if (strcmp(event_name, "KEY_T") == 0) return KEY_T ;
	if (strcmp(event_name, "KEY_Y") == 0) return KEY_Y ;
	if (strcmp(event_name, "KEY_U") == 0) return KEY_U ;
	if (strcmp(event_name, "KEY_I") == 0) return KEY_I ;
	if (strcmp(event_name, "KEY_O") == 0) return KEY_O ;
	if (strcmp(event_name, "KEY_P") == 0) return KEY_P ;
	if (strcmp(event_name, "KEY_LEFTBRACE") == 0) return KEY_LEFTBRACE ;
	if (strcmp(event_name, "KEY_RIGHTBRACE") == 0) return KEY_RIGHTBRACE ;
	if (strcmp(event_name, "KEY_ENTER") == 0) return KEY_ENTER ;
	if (strcmp(event_name, "KEY_LEFTCTRL") == 0) return KEY_LEFTCTRL ;
	if (strcmp(event_name, "KEY_A") == 0) return KEY_A ;
	if (strcmp(event_name, "KEY_S") == 0) return KEY_S ;
	if (strcmp(event_name, "KEY_D") == 0) return KEY_D ;
	if (strcmp(event_name, "KEY_F") == 0) return KEY_F ;
	if (strcmp(event_name, "KEY_G") == 0) return KEY_G ;
	if (strcmp(event_name, "KEY_H") == 0) return KEY_H ;
	if (strcmp(event_name, "KEY_J") == 0) return KEY_J ;
	if (strcmp(event_name, "KEY_K") == 0) return KEY_K ;
	if (strcmp(event_name, "KEY_L") == 0) return KEY_L ;
	if (strcmp(event_name, "KEY_SEMICOLON") == 0) return KEY_SEMICOLON ;
	if (strcmp(event_name, "KEY_APOSTROPHE") == 0) return KEY_APOSTROPHE ;
	if (strcmp(event_name, "KEY_GRAVE") == 0) return KEY_GRAVE ;
	if (strcmp(event_name, "KEY_LEFTSHIFT") == 0) return KEY_LEFTSHIFT ;
	if (strcmp(event_name, "KEY_BACKSLASH") == 0) return KEY_BACKSLASH ;
	if (strcmp(event_name, "KEY_Z") == 0) return KEY_Z ;
	if (strcmp(event_name, "KEY_X") == 0) return KEY_X ;
	if (strcmp(event_name, "KEY_C") == 0) return KEY_C ;
	if (strcmp(event_name, "KEY_V") == 0) return KEY_V ;
	if (strcmp(event_name, "KEY_B") == 0) return KEY_B ;
	if (strcmp(event_name, "KEY_N") == 0) return KEY_N ;
	if (strcmp(event_name, "KEY_M") == 0) return KEY_M ;
	if (strcmp(event_name, "KEY_COMMA") == 0) return KEY_COMMA ;
	if (strcmp(event_name, "KEY_DOT") == 0) return KEY_DOT ;
	if (strcmp(event_name, "KEY_SLASH") == 0) return KEY_SLASH ;
	if (strcmp(event_name, "KEY_RIGHTSHIFT") == 0) return KEY_RIGHTSHIFT ;
	if (strcmp(event_name, "KEY_KPASTERISK") == 0) return KEY_KPASTERISK ;
	if (strcmp(event_name, "KEY_LEFTALT") == 0) return KEY_LEFTALT ;
	if (strcmp(event_name, "KEY_SPACE") == 0) return KEY_SPACE ;
	if (strcmp(event_name, "KEY_CAPSLOCK") == 0) return KEY_CAPSLOCK ;
	if (strcmp(event_name, "KEY_F1") == 0) return KEY_F1 ;
	if (strcmp(event_name, "KEY_F2") == 0) return KEY_F2 ;
	if (strcmp(event_name, "KEY_F3") == 0) return KEY_F3 ;
	if (strcmp(event_name, "KEY_F4") == 0) return KEY_F4 ;
	if (strcmp(event_name, "KEY_F5") == 0) return KEY_F5 ;
	if (strcmp(event_name, "KEY_F6") == 0) return KEY_F6 ;
	if (strcmp(event_name, "KEY_F7") == 0) return KEY_F7 ;
	if (strcmp(event_name, "KEY_F8") == 0) return KEY_F8 ;
	if (strcmp(event_name, "KEY_F9") == 0) return KEY_F9 ;
	if (strcmp(event_name, "KEY_F10") == 0) return KEY_F10 ;
	if (strcmp(event_name, "KEY_NUMLOCK") == 0) return KEY_NUMLOCK ;
	if (strcmp(event_name, "KEY_SCROLLLOCK") == 0) return KEY_SCROLLLOCK ;
	if (strcmp(event_name, "KEY_KP7") == 0) return KEY_KP7 ;
	if (strcmp(event_name, "KEY_KP8") == 0) return KEY_KP8 ;
	if (strcmp(event_name, "KEY_KP9") == 0) return KEY_KP9 ;
	if (strcmp(event_name, "KEY_KPMINUS") == 0) return KEY_KPMINUS ;
	if (strcmp(event_name, "KEY_KP4") == 0) return KEY_KP4 ;
	if (strcmp(event_name, "KEY_KP5") == 0) return KEY_KP5 ;
	if (strcmp(event_name, "KEY_KP6") == 0) return KEY_KP6 ;
	if (strcmp(event_name, "KEY_KPPLUS") == 0) return KEY_KPPLUS ;
	if (strcmp(event_name, "KEY_KP1") == 0) return KEY_KP1 ;
	if (strcmp(event_name, "KEY_KP2") == 0) return KEY_KP2 ;
	if (strcmp(event_name, "KEY_KP3") == 0) return KEY_KP3 ;
	if (strcmp(event_name, "KEY_KP0") == 0) return KEY_KP0 ;
	if (strcmp(event_name, "KEY_KPDOT") == 0) return KEY_KPDOT ;
	if (strcmp(event_name, "KEY_ZENKAKUHANKAKU") == 0) return KEY_ZENKAKUHANKAKU ;
	if (strcmp(event_name, "KEY_102ND") == 0) return KEY_102ND ;
	if (strcmp(event_name, "KEY_F11") == 0) return KEY_F11 ;
	if (strcmp(event_name, "KEY_F12") == 0) return KEY_F12 ;
	if (strcmp(event_name, "KEY_RO") == 0) return KEY_RO ;
	if (strcmp(event_name, "KEY_KATAKANA") == 0) return KEY_KATAKANA ;
	if (strcmp(event_name, "KEY_HIRAGANA") == 0) return KEY_HIRAGANA ;
	if (strcmp(event_name, "KEY_HENKAN") == 0) return KEY_HENKAN ;
	if (strcmp(event_name, "KEY_KATAKANAHIRAGANA") == 0) return KEY_KATAKANAHIRAGANA ;
	if (strcmp(event_name, "KEY_MUHENKAN") == 0) return KEY_MUHENKAN ;
	if (strcmp(event_name, "KEY_KPJPCOMMA") == 0) return KEY_KPJPCOMMA ;
	if (strcmp(event_name, "KEY_KPENTER") == 0) return KEY_KPENTER ;
	if (strcmp(event_name, "KEY_RIGHTCTRL") == 0) return KEY_RIGHTCTRL ;
	if (strcmp(event_name, "KEY_KPSLASH") == 0) return KEY_KPSLASH ;
	if (strcmp(event_name, "KEY_SYSRQ") == 0) return KEY_SYSRQ ;
	if (strcmp(event_name, "KEY_RIGHTALT") == 0) return KEY_RIGHTALT ;
	if (strcmp(event_name, "KEY_LINEFEED") == 0) return KEY_LINEFEED ;
	if (strcmp(event_name, "KEY_HOME") == 0) return KEY_HOME ;
	if (strcmp(event_name, "KEY_UP") == 0) return KEY_UP ;
	if (strcmp(event_name, "KEY_PAGEUP") == 0) return KEY_PAGEUP ;
	if (strcmp(event_name, "KEY_LEFT") == 0) return KEY_LEFT ;
	if (strcmp(event_name, "KEY_RIGHT") == 0) return KEY_RIGHT ;
	if (strcmp(event_name, "KEY_END") == 0) return KEY_END ;
	if (strcmp(event_name, "KEY_DOWN") == 0) return KEY_DOWN ;
	if (strcmp(event_name, "KEY_PAGEDOWN") == 0) return KEY_PAGEDOWN ;
	if (strcmp(event_name, "KEY_INSERT") == 0) return KEY_INSERT ;
	if (strcmp(event_name, "KEY_DELETE") == 0) return KEY_DELETE ;
	return -1;
}
