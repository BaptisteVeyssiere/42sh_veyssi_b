/*
** env.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed Mar 30 16:30:09 2016 Baptiste veyssiere
** Last update Mon May 30 01:15:40 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include "mysh.h"

int	env_builtin(char ***env, UNUSED char **command)
{
  int	i;

  i = -1;
  if (!(*env))
    return (0);
  while ((*env)[++i])
    if (write(1, (*env)[i], my_strlen((*env)[i])) == -1 ||
	write(1, "\n", 1) == -1)
      return (-1);
  return (0);
}
