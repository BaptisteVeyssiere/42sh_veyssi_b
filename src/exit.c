/*
** exit.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed Mar 30 16:35:16 2016 Baptiste veyssiere
** Last update Wed Jun  1 09:50:54 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static int	check_formation(char *str)
{
  int		i;

  i = -1;
  while (str[++i])
    {
      if (str[i] > '9' || str[i] < '0')
	{
	  if (i != 0 || str[i] != '-')
	    return (-1);
	}
    }
  return (0);
}

static int	error_exit(char **command)
{
  if (check_formation(command[1]) == -1)
    return (my_int_perror("exit: Badly formed number.\n", 1));
  if (my_tablen(command) != 2)
    return (my_int_perror("exit: Expression Syntax.\n", 1));
  return (0);
}

int	exit_builtin(char ***env, char **command)
{
  int	nbr;

  env = env;
  if (!command[1])
    nbr = 0;
  else
    {
      if (error_exit(command) == 1)
	return (1);
      nbr = my_getnbr(command[1]);
    }
  return (nbr);
}
