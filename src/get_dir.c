/*
** get_dir.c for 42sh in /home/semmao_i/rendu/PSU/PSU_2015_42sh
** 
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
** 
** Started on  Sat Jun  4 23:54:09 2016 ilyas semmaoui
** Last update Sun Jun  5 00:01:05 2016 ilyas semmaoui
*/

#include <stdlib.h>
#include <mysh.h>

char	*my_getdir(char *str)
{
  int	i;
  int	cp;
  char	*path;

  cp = 0;
  i = -1;
  while (str && str[++i])
    if (str[i] == '/')
      cp = i;
  if ((path = malloc(cp + 1)) == NULL)
    return (NULL);
  i = -1;
  while (++i < cp && str && str[i])
    path[i] = str[i];
  path[i] = 0;
  return (path);
}
