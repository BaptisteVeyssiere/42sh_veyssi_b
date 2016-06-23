/*
** get_varenv.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue Mar 29 18:45:54 2016 Baptiste veyssiere
** Last update Sun Apr 10 04:13:53 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

char	*get_varenv(char **env, char *str)
{
  char	*var;
  int	i;
  int	j;
  int	length;

  i = -1;
  if (env == NULL || env[0] == NULL)
    return (NULL);
  while (env[++i] != NULL && !my_strcmp(str, env[i]));
  if (env[i] == NULL)
    return (NULL);
  j = 0;
  while (env[i][j] != '=')
    ++j;
  ++j;
  length = -1;
  length = my_strlen(env[i]) - j;
  if ((var = malloc(sizeof(char) * (length + 1))) == NULL)
    return (NULL);
  var[length] = 0;
  length = -1;
  --j;
  while (env[i][++j])
    var[++length] = env[i][j];
  return (var);
}
