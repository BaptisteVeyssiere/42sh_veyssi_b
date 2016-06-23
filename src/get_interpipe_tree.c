/*
** get_interpipe_tree.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 21:37:48 2016 Baptiste veyssiere
** Last update Thu May 26 00:05:08 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static int	get_interpipe_nbr(char *command)
{
  int		nbr;
  int		i;

  i = -1;
  nbr = 0;
  while (command[++i])
    if (command[i] == '|')
      ++nbr;
  return (nbr);
}

static int	get_interpipe_length(char *command, int pos)
{
  int		length;
  int		i;

  length = 0;
  i = pos;
  while (command[++i] && command[i] != '|')
    ++length;
  if (i > 0 && (command[i - 1] == ' ' || command[i - 1] == '\t'))
    --length;
  return (length);
}

static char	*get_interpipe(char *command, int *pos)
{
  char		*tabi;
  int		length;
  int		i;

  tabi = NULL;
  length = get_interpipe_length(command, *pos);
  if (!(tabi = malloc(length + 1)))
    return (NULL);
  tabi[length] = 0;
  i = -1;
  while (++i < length)
    tabi[i] = command[++(*pos)];
  while (command[++(*pos)] == ' ' || command[*pos] == '\t' ||
         command[*pos] == '|');
  --(*pos);
  return (tabi);
}

static char	**get_interpipe_tab(char *command, int interpipe_nbr)
{
  char		**tab;
  int		i;
  int		pos;

  tab = NULL;
  if (!(tab = malloc(sizeof(char*) * (interpipe_nbr + 2))))
    return (NULL);
  tab[interpipe_nbr + 1] = NULL;
  i = -1;
  pos = -1;
  while (++i <= interpipe_nbr)
    if (!(tab[i] = get_interpipe(command, &pos)))
      return (NULL);
  return (tab);
}

t_command	*get_interpipe_tree(char *command)
{
  t_command	*and_or;
  int		interpipe_nbr;
  int		i;
  char		**tab;

  interpipe_nbr = get_interpipe_nbr(command);
  if (!(and_or = malloc(sizeof(t_command))))
    return (NULL);
  and_or->pipe_nbr = interpipe_nbr;
  if (!(and_or->command = malloc(sizeof(t_command*) * (interpipe_nbr + 2))))
    return (NULL);
  if (!(tab = get_interpipe_tab(command, interpipe_nbr)))
    return (NULL);
  and_or->command[interpipe_nbr + 1] = NULL;
  i = -1;
  while (++i <= interpipe_nbr)
    if (!(and_or->command[i] = get_command_tree(tab[i])))
      return (NULL);
  free_tab(tab);
  return (and_or);
}
