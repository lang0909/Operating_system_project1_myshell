/**********************************************************************
 * Copyright (C) Jaewon Choi <jaewon.james.choi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 *********************************************************************/
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void parse_command(const char* input,
                   int* argc, char*** argv)
{
  int a = -1;
  int b = *argc;
  char str[200]={0,};
  strcpy(str,input);
  *argv= (char**)malloc(sizeof(char*)*b);
  char * str1= strtok(str," ");
  do
  {
    a= a+1;
    argv[a] = *argv+a;
    *argv[a] = (char*)malloc(sizeof(char)*(strlen(str1)+1));
    strcpy(*argv[a],str1);
  }while(str1=strtok(NULL," "));

  a++;
  argv[a] = *argv+a;
  *argv[a] = (char*)malloc(sizeof(char));
  *argv[a] = NULL;
  // TODO: Fill it!z
}


/*
{
  *argc=-1;
  char str[200]={0,};
  strcpy(str,input);
  *argv= (char**)malloc(sizeof(char*));
  char * str1= strtok(str," ");
  do
  {
    (*argc)++;
    argv[*argc] = *argv+(*argc);
    *argv[*argc] = (char*)malloc(sizeof(char));
    strcpy(*argv[*argc],str1);
  }while(str1=strtok(NULL," "));

  (*argc)++;
  argv[*argc] = *argv+(*argc);
  *argv[*argc] = (char*)malloc(sizeof(char));
  *argv[*argc] = NULL;
  // TODO: Fill it!z
}
*/