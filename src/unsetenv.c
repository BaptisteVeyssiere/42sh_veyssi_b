/*
** unsetenv.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed Mar 30 16:41:28 2016 Baptiste veyssiere
** Last update Tue May 31 01:02:03 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

static char	**unset_var(char **env, int index)
{
  char		**copy;
  int		length;
  int		i;
  int		minus;

  if (!env[0])
    return (NULL);
  length = -1;
  while (env[++length]);
  if (!(copy = malloc(sizeof(char*) * length)))
    return (NULL);
  copy[length - 1] = NULL;
  i = -1;
  minus = 0;
  while (++i < length)
    {
      if (i == index)
	minus = 1;
      if (i != index && !(copy[i - minus] = copy_varenv(env[i])))
	return (NULL);
    }
  free_env(env);
  return (copy);
}

static char	**unsetenv_var_of_env(char **env, char **command)
{
  int		i;
  char		*var;
  char		**new_env;

  if (!(var = malloc(my_strlen(command[1] + 2))))
    return (NULL);
  i = -1;
  while (command[1][++i] && command[1][i] != '=')
    var[i] = command[1][i];
  var[i] = '=';
  var[++i] = 0;
  i = -1;
  if (env)
    while (env[++i] && !my_strcmp(var, env[i]));
  if (env[i] == NULL)
    {
      free(var);
      return (env);
    }
  else if ((new_env = unset_var(env, i)) == NULL)
    return (NULL);
  free(var);
  return (new_env);
}

int	unsetenv_builtin(char ***env, char **command)
{
  int	arg_nbr;
  char	**new_env;

  arg_nbr = my_tablen(command);
  if (arg_nbr < 2)
    return (my_int_perror("unsetenv: Too few arguments.\n", 1));
  else if (arg_nbr > 2)
    return (my_int_perror("unsetenv: Too few arguments.\n", 1));
  else if (!env)
    return (0);
  if (!(new_env = unsetenv_var_of_env(*env, command)))
    return (-1);
  *env = new_env;
  return (0);
}
