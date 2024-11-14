#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef GAMEPAD_H
#include "gamepad.h"
#endif

#define PROPERTY_SIZE 128

int is_section(const char* section, char* section_name)
{
    /* strlen -2 because of \n */
    int rc = section[0] == '[' && section[strlen(section) - 2] == ']';
    if(rc)
        strncpy(section_name, section + 1, strlen(section) -2);
    return rc;
}

int is_comment(const char* line)
{
    return line[0] == '#';
}

int get_property_value(const char* line, char* property_name, char* property_value)
{
    size_t position;
    char* p = strchr(line, '=');
    position = (size_t)(p - line);
    if (p == NULL)
        return 0;
    
    size_t len = strlen(line);
    char* dest_str = property_name;
    int i = 0;
    int token_pos = 0;
    
    do
    {
        if (line[i] == '=')
        {
            property_name[i] = '\0';
            dest_str = property_value;
            printf("Found = at position %d\n", i);
            token_pos = i + 1;
            continue;
        }
        dest_str[i - token_pos] = line[i];
    }
    while (line[++i] != '\0');
    /* Get rid of the last \n */
    dest_str[i - token_pos - 1] = '\0';
    
    return 1;
}

int read_ini(char* ini_file)
{
    FILE *fp;
    char *line = NULL;
    
    char section[128];
    char property[256];
    char value[32];
    size_t len = 0;
    ssize_t read;
    uint8_t gamepads_found = 0;
    static const GPdata EmptyGPData;
    GPdata pad;


    fp = fopen(ini_file, "r");
    if (fp == NULL)
        return -1;

    /* Boring cases to handle:
        - got properties out of a section
        - section is not in the valid format (a SDL GUID, gamepad name, or VID:PID)
          as for now, it just considers it is a SDL GUID
        - cycle through various sections and store the last one
    */

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        if(is_comment(line))
            printf("\t-> is a comment\n");
        else if (is_section(line, section))
        {
            printf("\t-> is a section header: %s\n", section);
            pad = EmptyGPData;
            strcpy( pad.gamepad_name, "Testing pad");
            pad.guid = SDL_GUIDFromString(section);
        }
        else if (get_property_value(line, property, value))
        {
            printf("\t-> property = %s\n", property);
            printf("\t-> value    = %s (%d)\n", value, get_event_value_from_name(value));
            gamepad_assign_key(&pad.mapping, property, get_event_value_from_name(value));
        }
        else
            printf("\t-> not used\n");

    }
    print_gamepad(&pad);
    free(line);
    
}