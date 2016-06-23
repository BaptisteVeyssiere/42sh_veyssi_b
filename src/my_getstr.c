/*
** my_getstr.c for my_getstr in /home/semmao_i/rendu/PSU_2015_42sh
**
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
**
** Started on  Fri Jun  3 17:03:16 2016 ilyas semmaoui
** Last update Wed Jun  8 16:06:27 2016 Baptiste veyssiere
*/

#include <stdlib.h>

char	*my_getstr(int  nbr)
{
  char	*str;
  int   i;
  int   n;
  int   div;

  div = 1;
  i = 0;
  n = nbr;
  while (n / 10 != 0 && ++i)
    n = n / 10;
  if ((str = malloc(sizeof(char) * (i + 2))) == NULL)
    return (NULL);
  while (--i > 0)
    div = div * 10;
  if ((i = -1) == -1 && nbr < 0 && (nbr = (nbr * -1)) >= 0)
    str[++i] = '-';
  while (div > 0)
    {
      str[++i] = ((nbr / div) + 48);
      nbr = nbr % div;
      div = div / 10;
    }
  str[++i] = '\0';
  return (str);
}
