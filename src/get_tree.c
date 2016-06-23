/*
** get_tree.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 17:18:44 2016 Baptiste veyssiere
** Last update Sat Jun  4 18:33:44 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

static int	get_semicolon_nbr(char *command)
{
  int		i;
  int		nbr;

  i = -1;
  nbr = 0;
  while (command[++i])
    if (command[i] == ';')
      ++nbr;
  return (nbr);
}

static int	get_command_length(char *command, int pos)
{
  int		length;
  int		i;

  length = 0;
  i = pos;
  while (command[++i] && command[i] != ';')
    ++length;
  if (i > 0 && (command[i - 1] == ' ' || command[i - 1] == '\t'))
    --length;
  return (length);
}

static char	*get_command(char *command, int *pos)
{
  char		*tabi;
  int		length;
  int		i;

  length = get_command_length(command, *pos);
  if (!(tabi = malloc(length + 1)))
    return (NULL);
  tabi[length] = 0;
  i = -1;
  while (++i < length)
    tabi[i] = command[++(*pos)];
  while (command[++(*pos)] == ' ' ||
	 command[*pos] == '\t' || command[*pos] == ';');
  --(*pos);
  return (tabi);
}

static char	**get_command_tab(char *command, int semicolon_nbr)
{
  char		**tab;
  int		i;
  int		pos;

  tab = NULL;
  if (!(tab = malloc(sizeof(char*) * (semicolon_nbr + 2))))
    return (NULL);
  tab[semicolon_nbr + 1] = NULL;
  i = -1;
  pos = -1;
  while (++i <= semicolon_nbr)
    if (!(tab[i] = get_command(command, &pos)))
      return (NULL);
  return (tab);
}

int	get_tree(t_tree ***tree, char *command)
{
  int	semicolon_nbr;
  char	**tab;
  int	i;

  *tree = NULL;
  semicolon_nbr = get_semicolon_nbr(command);
  if (!(tab = get_command_tab(command, semicolon_nbr)))
    return (-1);
  if (!(*tree = malloc(sizeof(t_tree*) * (semicolon_nbr + 2))))
    return (-1);
  i = -1;
  while (++i <= (semicolon_nbr + 1))
    (*tree)[i] = NULL;
  i = -1;
  while (++i <= semicolon_nbr)
    if (!((*tree)[i] = get_and_or_tree(tab[i])))
      return (-1);
  free_tab(tab);
  return (0);
}
