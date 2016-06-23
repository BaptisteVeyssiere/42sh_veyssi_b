/*
** get_and_or_tree_add.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 23:52:57 2016 Baptiste veyssiere
** Last update Thu May 26 00:21:02 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

char	*get_inter_tab(char *command, int and_or_nbr)
{
  char	*tab;
  int	i;
  int	j;

  if (!(tab = malloc(and_or_nbr + 1)))
    return (NULL);
  tab[and_or_nbr] = 0;
  i = -1;
  j = -1;
  while (command[++i])
    if (command[i] == '|' && command[i + 1] == '|')
      tab[++j] = 2;
    else if (command[i] == '&' && command[i + 1] == '&')
      tab[++j] = 1;
  return (tab);
}

void	apply_and_or(t_command *interpipe, char *and_or, int i)
{
  interpipe->and = 0;
  interpipe->or = 0;
  if (i > 0)
    {
      if (and_or[i - 1] == 1)
	interpipe->and = 1;
      else if (and_or[i - 1] == 2)
	interpipe->or = 1;
    }
}
