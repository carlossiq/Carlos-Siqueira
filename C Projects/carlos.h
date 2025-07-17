// biblioteca para C
//  #ifndef CARLOS_LIBRARY_H
//  #define CARLOS_LIBRARY_H

// #endif

#pragma once

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef char *string;

int getInt(string s)
{
    int value = 0;
    if (s != NULL && strlen(s) != 0)
    {
        printf("%s\n", s);
    }
    scanf("%i", &value);
    return value;
}

string getString(string s)
{
    if( s != '/0' && s != NULL)
    {
        printf("%s", s);
    }
    scanf(" %[^\n]", s);
    return s;
}

typedef enum
{
    false,
    true
} bool;