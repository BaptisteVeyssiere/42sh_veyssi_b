/*
** str_to_wordtab.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue Mar 29 17:41:31 2016 Baptiste veyssiere
** Last update Sat Jun  4 16:40:32 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static int	get_word_nbr(char *str)
{
  int		i;
  int		nbr;

  i = -1;
  nbr = 0;
  while (str[++i])
    {
      if ((i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t') &&
	  (str[i] != ' ' && str[i] != '\t'))
	++nbr;
    }
  return (nbr);
}

static char	*str_to_word(char *str, int i)
{
  int		length;
  int		j;
  char		*tabi;

  length = -1;
  while (str[++length + i] &&
	 str[length + i] != ' ' && str[length + i] != '\t');
  ++length;
  if ((tabi = malloc(sizeof(char) * (length + 1))) == NULL)
    return (NULL);
  j = -1;
  while (++j <= length)
    tabi[j] = 0;
  j = -1;
  while (str[i] && str[i] != ' ' && str[i] != '\t')
    {
      tabi[++j] = str[i];
      ++i;
    }
  return (tabi);
}

char	**str_to_wordtab(char *str)
{
  char	**tab;
  int	word_nbr;
  int	i;
  int	j;

  word_nbr = get_word_nbr(str);
  if ((tab = malloc(sizeof(char*) * (word_nbr + 1))) == NULL)
    return (NULL);
  tab[word_nbr] = NULL;
  i = -1;
  j = -1;
  while (str[++i])
    {
      if ((i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t') &&
          (str[i] != ' ' && str[i] != '\t'))
	if ((tab[++j] = str_to_word(str, i)) == NULL)
	  return (NULL);
    }
  return (tab);
}
