#ifndef GAMEPAD_H
#include "gamepad.h"
#endif

const GPmapping default_gamepad = { KEY_ENTER, KEY_ESC, 0, 0, 
    KEY_TAB, 0, KEY_ENTER, 
    0, 0, 
    KEY_PAGEUP, KEY_PAGEDOWN,
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 
    0, 0, 0, 0,
    0, 0, 0
    };

GPdata default_gpdata = { .mapping = default_gamepad };

GPdata GPmap[GAMEPAD_MAP_SIZE];

void print_gamepad(GPdata* gp)
{
    char strguid[64];
    SDL_GUIDToString(gp->guid, strguid, 64);
    printf("Gamepad name: %s\n"
        "GUID:         %s\n"  
        "VID:PID:      %d:%d\n"
        "a:            %d\n"
        "b:            %d\n"
        "x:            %d\n"
        "y:            %d\n"
        "back:         %d\n"
        "guide:        %d\n"
        "start:        %d\n"
        "leftshoulder: %d\n"
        "rightshoulder:%d\n"
        "dpup:         %d\n"
        "dpdown:       %d\n"
        "dpleft:       %d\n"
        "dpright:      %d\n"
        , gp->gamepad_name
        , strguid
        , gp->vid, gp->pid
        , gp->mapping.a
        , gp->mapping.b
        , gp->mapping.x
        , gp->mapping.y
        , gp->mapping.back
        , gp->mapping.guide
        , gp->mapping.start
        , gp->mapping.leftshoulder
        , gp->mapping.rightshoulder
        , gp->mapping.dpup
        , gp->mapping.dpdown
        , gp->mapping.dpleft
        , gp->mapping.dpright
    );
}

int gamepad_assign_key(GPmapping* mapping, const char* event_name, const int event_value)
{
    int found;
    if (strcmp(event_name, "a") == 0) 
    {
        printf("Mapping a to %d\n", event_value);
        mapping->a = event_value;
        return 1 ;
    }
    if (strcmp(event_name, "b") == 0) 
    {
        printf("Mapping b to %d\n", event_value);
        mapping->b = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "x") == 0) 
    {
        printf("Mapping x to %d\n", event_value);
        mapping->x = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "y") == 0) 
    {
        printf("Mapping y to %d\n", event_value);
        mapping->y = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "back") == 0) 
    {
        printf("Mapping back to %d\n", event_value);
        mapping->back = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "guide") == 0) 
    {
        printf("Mapping guide to %d\n", event_value);
        mapping->guide = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "start") == 0) 
    {
        printf("Mapping start to %d\n", event_value);
        mapping->start = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "leftshoulder") == 0) 
    {
        printf("Mapping leftshoulder to %d\n", event_value);
        mapping->leftshoulder = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "rightshoulder") == 0) 
    {
        printf("Mapping rightshoulder to %d\n", event_value);
        mapping->rightshoulder = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "dpup") == 0) 
    {
        printf("Mapping dpup to %d\n", event_value);
        mapping->dpup = event_value;
        return 1 ;
    }
    if (strcmp(event_name, "dpdown") == 0) 
    {
        printf("Mapping dpdown to %d\n", event_value);
        mapping->dpdown = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "dpleft") == 0) 
    {
        printf("Mapping dpleft to %d\n", event_value);
        mapping->dpleft = event_value;
        return 1 ;
    }  
    if (strcmp(event_name, "dpright") == 0) 
    {
        printf("Mapping dpright to %d\n", event_value);
        mapping->dpright = event_value;
        return 1 ;
    }  
    return 0;
}