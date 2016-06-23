/*
** alias_tools_bis.c for mysh in /home/scutar_n/rendu/PSU/PSU_2015_42sh
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Sun Jun  5 22:37:21 2016 Nathan Scutari
** Last update Sun Jun  5 22:44:02 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

t_alias		*manage_ret(t_alias *old, t_alias *alias, int fd)
{
  if (!alias)
    return (old);
  else if (old)
    {
      if (close(old->source) == -1)
	return (NULL);
      free_alias(old);
    }
  alias->source = fd;
  return (alias);
}

void	init_var(int *x, char **alias, char **equivalent)
{
  *x = -1;
  *alias = NULL;
  *equivalent = NULL;
}

int	free_errors(char *alias, char *equivalent)
{
  if (alias)
    free(alias);
  if (equivalent)
    free(equivalent);
  return (0);
}
