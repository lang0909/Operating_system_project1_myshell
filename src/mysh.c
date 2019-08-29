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
#include "parser.h"
#include "utils.h"
#include "fs.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

void signal_generator()
{

}

void signal_handler()
{

}

int main()
{
  char command_buffer[4096] = { 0, };
  while (fgets(command_buffer, 4096, stdin) != NULL) 
  {
    int argc = 0;
    char** argv = NULL;
    if(command_buffer[strlen(command_buffer)-1]=='\n')
    {
      command_buffer[strlen(command_buffer)-1] ='\0';
    }
    for(int i=0;i<strlen(command_buffer);i++)
    {
      if(command_buffer[i]==' ')
      {
        argc++;
      }
    }
    argc = argc+2;
    parse_command(command_buffer, &argc, &argv);
    assert(argv != NULL);
    if (strcmp(argv[0], "exit") == 0) {
      FREE_2D_ARRAY(argc, argv);
      break;
    }

    struct command_entry* comm_entry = fetch_command(argv[0]);

    if (comm_entry != NULL) 
    {
      int ret = comm_entry->command_func(argc, argv);
      if (ret != 0) 
      {
        comm_entry->err(ret);
      }
    } 
    else if (does_exefile_exists(argv[0])==1)
    {
      // TODO: Execute the program of argv[0].
      pid_t pid;
      pid = fork();
      if(pid==0)
      {
        execvp(argv[0],argv);
        FREE_2D_ARRAY(argc, argv);
      }
      else if(pid>0)
      {
        wait(NULL);
      }
    }
    else if(resolve_path(argv[0])==1)
    {
      pid_t pid;
      pid = fork();
      if(pid==0)
      {
        execvp(argv[0],argv);
        FREE_2D_ARRAY(argc, argv);
      }
      else if(pid>0)
      {
        wait(NULL);
      }
    }
    else 
    {
      assert(comm_entry == NULL);
      fprintf(stderr, "%s: command not found.\n", argv[0]);
    }
    FREE_2D_ARRAY(argc, argv);
  }

  return 0;
}
