/*
** epure_str.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 17:52:01 2016 Baptiste veyssiere
** Last update Sun Jun  5 17:47:38 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

static int	get_epure_length(char *str)
{
  int		length;
  int		i;

  if (!str)
    return (0);
  length = 0;
  i = -1;
  while (str[++i] && (str[i] == ' ' || str[i] == '\t'));
  if (!str[i])
    return (0);
  --i;
  while (str[++i])
    if ((str[i] != ' ' && str[i] != '\t') ||
	((str[i] == ' ' || str[i] == '\t') &&
	 str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\t'))
      ++length;
  return (length);
}

char	*epure_str(char *str)
{
  int	epure_length;
  char	*epure;
  int	i;
  int	j;

  epure = NULL;
  epure_length = get_epure_length(str);
  if (!str || !(epure = malloc(epure_length + 1)))
    return (NULL);
  i = -1;
  while (++i <= epure_length)
    epure[i] = 0;
  i = -1;
  j = -1;
  while (str[++i] && (str[i] == ' ' || str[i] == '\t'));
  if (!str[i])
    return (epure);
  --i;
  while (str[++i])
    if ((str[i] != ' ' && str[i] != '\t') ||
        ((str[i] == ' ' || str[i] == '\t') &&
         str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\t'))
      epure[++j] = str[i];
  return (epure);
}
