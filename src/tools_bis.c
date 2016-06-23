/*
** tools_bis.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Mon May 30 01:33:29 2016 Baptiste veyssiere
** Last update Sat Jun  4 17:10:04 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

int	my_strcat(char *to, char *from)
{
  int	i;
  int	j;

  i = -1;
  j = -1;
  while (to[++i] != 0);
  while (from[++j] != 0)
    {
      to[i] = from[j];
      i += 1;
    }
  return (0);
}

char	*my_malloc(int size)
{
  char	*ret;
  int	i;

  i = -1;
  if ((ret = malloc(size)) == NULL)
    return (NULL);
  while (++i < size)
    ret[i] = 0;
  return (ret);
}

int	my_tablen(char **tab)
{
  int	i;
  int	nbr;

  i = -1;
  nbr = 0;
  if (!tab)
    return (0);
  while (tab[++i])
    ++nbr;
  return (nbr);
}

int	my_getnbr(char *str)
{
  int   i;
  int   j;
  int   limit;
  int   nbr;

  i = 0;
  nbr = 0;
  limit = 0;
  if (str[0] == '-')
    limit = 1;
  while (str[i] != 0)
    i++;
  i--;
  j = 1;
  while (i >= limit)
    {
      nbr += j * (str[i--] - 48);
      j *= 10;
    }
  if (str[0] == '-')
    nbr *= -1;
  return (nbr);
}
