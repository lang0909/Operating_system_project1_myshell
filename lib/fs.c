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
#include "fs.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int does_exefile_exists(const char* path)
{
  // TODO: Fill it!
  struct stat buf;
  stat(path,&buf);
  if((buf.st_mode&S_IRWXU)||(buf.st_mode&S_IRWXG)||(buf.st_mode&S_IRWXO))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int resolve_path(char*path1)
{
  int a=0;
  char *ptr[30]={0,};
  char *str=NULL;
  char str2[100]={0,};
  str = getenv("PATH");
  strcpy(str2,str);
  char * str1= strtok(str2,":");
  do
  {
    ptr[a] = (char*)malloc(sizeof(char)*(strlen(str1)+strlen(path1)+2));
    strcpy(ptr[a],str1);
    a++;
  }while(str1=strtok(NULL,":"));


  for(int i=0;i<a;i++)
  {
    strcat(ptr[i],"/");
    strcat(ptr[i],path1);
    if(does_exefile_exists(ptr[i])==1)
    {
      strcpy(path1,ptr[i]);
      return 1;
    }
  }
  return 0;
}
