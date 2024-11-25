#pragma once

#define INTERPRET_SIZE 21
#define NAME_SIZE 21

struct t_album
{
    char  interpret[INTERPRET_SIZE];
    char  name[NAME_SIZE];
    int   rok;
    struct t_album* dalsi;
};

void add(char* interpret, char* znacka, int rok, struct t_album** uk_prvni);
void del(int rok, struct t_album** uk_prvni);
