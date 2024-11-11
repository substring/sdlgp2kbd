#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PROPERTY_SIZE 128

int is_section(const char* section)
{
    /* strlen -2 because of \n */
    return section[0] == '[' && section[strlen(section) - 2] == ']';
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
    dest_str[i - token_pos] = '\0';
    
    return 1;
}

int read_ini(char* ini_file)
{
    FILE *fp;
    char *line = NULL;
    char property[256];
    char value[32];
    size_t len = 0;
    ssize_t read;

    fp = fopen(ini_file, "r");
    if (fp == NULL)
        return -1;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        if(is_comment(line))
            printf("\t-> is a comment\n");
        else if (is_section(line))
            printf("\t-> is a section header\n");
        else if (get_property_value(line, property, value))
        {
            printf("\t-> property = %s\n", property);
            printf("\t-> value    = %s\n", value);
        }
        else
            printf("\t-> not used\n");

    }

    free(line);
    
}