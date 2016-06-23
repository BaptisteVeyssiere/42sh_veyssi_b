/*
** env_copy.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed Mar 30 16:01:44 2016 Baptiste veyssiere
** Last update Sun Apr 10 04:37:25 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

void	free_env(char **env)
{
  int	i;

  i = -1;
  while (env != NULL && env[++i] != NULL)
    free(env[i]);
  free(env);
}

char	*copy_varenv(char *envi)
{
  char	*copy;
  int	length;
  int	i;

  length = -1;
  while (envi[++length]);
  if ((copy = malloc(sizeof(char) * (length + 1))) == NULL)
    return (NULL);
  copy[length] = 0;
  i = -1;
  while (++i < length)
    copy[i] = envi[i];
  return (copy);
}

char	**env_copy(char **env)
{
  char	**copy;
  int	length;
  int	i;

  if (env[0] == NULL)
    return (NULL);
  length = -1;
  while (env[++length] != NULL);
  if ((copy = malloc(sizeof(char*) * (length + 1))) == NULL)
    return (NULL);
  copy[length] = NULL;
  i = -1;
  while (++i < length)
    if ((copy[i] = copy_varenv(env[i])) == NULL)
      return (NULL);
  return (copy);
}
