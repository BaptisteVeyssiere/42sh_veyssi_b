/*
** tools.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 17:25:32 2016 Baptiste veyssiere
** Last update Sat May 28 22:37:45 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>

int	my_strlen(char *str)
{
  int	i;

  if (!str)
    return (0);
  i = -1;
  while (str[++i]);
  return (i);
}

void	my_strcpy(char *origin, char *copy)
{
  int	i;

  i = -1;
  while (origin[++i])
    copy[i] = origin[i];
  copy[i] = 0;
}

int	my_strcmp_strict(char *s1, char *s2)
{
  int   i;

  i = -1;
  while (s1[++i])
    if (s1[i] != s2[i])
      return (0);
  if (s2[i])
    return (0);
  return (1);
}

char	*free_line(char *line, char *ret)
{
  free(line);
  if (ret == NULL)
    return (NULL);
  return (ret);
}

int	my_strcmp(char *s1, char *s2)
{
  int   i;

  i = -1;
  while (s1[++i])
    {
      if (s1[i] != s2[i])
	return (0);
    }
  return (1);
}
