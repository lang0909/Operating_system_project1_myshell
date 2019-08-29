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
#include "commands.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

static struct command_entry commands[] =
{
  {
    "pwd",
    do_pwd,
    err_pwd
  },
  {
    "cd",
    do_cd,
    err_cd
  }
};

struct command_entry* fetch_command(const char* command_name)
{
  // TODO: Fill it.
  if(strcmp(command_name,"pwd")==0)
  {
    return &commands[0];
  }
  if(strcmp(command_name,"cd")==0)
  {
    return &commands[1];
  }
  return NULL;
}

int do_pwd(int argc, char** argv)
{
  // TODO: Fill it.
  char ptr[200]={0,};
  getcwd(ptr, 200);
  printf("%s\n", ptr);
  return 0;
}

void err_pwd(int err_code)
{
  // TODO: Fill it.
}

int do_cd(int argc, char** argv)
{
  // TODO: Fill it.
  struct stat buf;
  if(access(argv[1],F_OK)==0)
  {
    stat(argv[1],&buf);
    if(S_ISDIR(buf.st_mode))
    {
      chdir(argv[1]);
      return 0;
    }
    else
    {
      return 2;
    }
  }
  else
  {
    return 1;
  }
}

void err_cd(int err_code)
{
  // TODO: Fill it.
  if(err_code == 1)
  {
    fprintf(stderr,"cd: no such file or directory\n");
  }
  else if(err_code == 2)
  {
    fprintf(stderr,"cd: not a directory\n");
  }
}
