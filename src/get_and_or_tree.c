/*
** get_and_or_tree.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 20:49:46 2016 Baptiste veyssiere
** Last update Thu May 26 00:20:44 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static int	get_and_or_nbr(char *command)
{
  int		nbr;
  int		i;

  i = -1;
  nbr = 0;
  while (command[++i])
    if ((command[i] == '|' && command[i + 1] == '|') ||
	(command[i] == '&' && command[i + 1] == '&'))
      ++nbr;
  return (nbr);
}

static int	get_and_or_length(char *command, int pos)
{
  int		length;
  int		i;

  length = 0;
  i = pos;
  while (command[++i] &&
	 (command[i] != '|' || command[i + 1] != '|') &&
	 (command[i] != '&' || command[i + 1] != '&'))
    ++length;
  if (i > 0 && (command[i - 1] == ' ' || command[i - 1] == '\t'))
    --length;
  return (length);
}

static char	*get_and_or(char *command, int *pos)
{
  char		*tabi;
  int		length;
  int		i;

  tabi = NULL;
  length = get_and_or_length(command, *pos);
  if (!(tabi = malloc(length + 1)))
    return (NULL);
  tabi[length] = 0;
  i = -1;
  while (++i < length)
    tabi[i] = command[++(*pos)];
  while (command[++(*pos)] == ' ' || command[*pos] == '\t' ||
         command[*pos] == '|' || command[*pos] == '&');
  --(*pos);
  return (tabi);
}

static char	**get_and_or_tab(char *command, int and_or_nbr)
{
  char		**tab;
  int		i;
  int		pos;

  tab = NULL;
  if (!(tab = malloc(sizeof(char*) * (and_or_nbr + 2))))
    return (NULL);
  tab[and_or_nbr + 1] = NULL;
  i = -1;
  pos = -1;
  while (++i <= and_or_nbr)
    if (!(tab[i] = get_and_or(command, &pos)))
      return (NULL);
  return (tab);
}

t_tree		*get_and_or_tree(char *command)
{
  t_tree	*tree;
  int		and_or_nbr;
  char		*and_or;
  int		i;
  char		**tab;

  and_or_nbr = get_and_or_nbr(command);
  if (!(tree = malloc(sizeof(t_tree))))
    return (NULL);
  tree->and_or_nbr = and_or_nbr;
  if (!(tree->and_or = malloc(sizeof(t_command*) * (and_or_nbr + 2))) ||
      !(tab = get_and_or_tab(command, and_or_nbr)) ||
      !(and_or = get_inter_tab(command, and_or_nbr)))
    return (NULL);
  tree->and_or[and_or_nbr + 1] = NULL;
  i = -1;
  while (++i <= and_or_nbr)
    {
      if (!(tree->and_or[i] = get_interpipe_tree(tab[i])))
	return (NULL);
      apply_and_or(tree->and_or[i], and_or, i);
    }
  free_tab(tab);
  free(and_or);
  return (tree);
}
