/*
** setenv.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed Mar 30 16:40:11 2016 Baptiste veyssiere
** Last update Thu Jun  2 12:00:43 2016 vigner_g
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static char	*new_var(char **command)
{
  char		*var;
  int		i;
  int		j;
  int		length;

  length = my_strlen(command[1]) + 1 + my_strlen(command[2]);
  if (!(var = malloc(length + 1)))
    return (NULL);
  var[length] = 0;
  i = -1;
  while (command[1][++i] && command[1][i] != '=')
    var[i] = command[1][i];
  var[i] = '=';
  j = -1;
  if (command[2])
    while (command[2][++j])
      var[++i] = command[2][j];
  return (var);
}

static char	**reset_varenv(char **env, char **command, int index)
{
  char		**copy;
  int		length;
  int		i;

  if (!env || !env[0])
    return (NULL);
  length = -1;
  while (env && env[++length]);
  if (!(copy = malloc(sizeof(char*) * (length + 1))))
    return (NULL);
  copy[length] = NULL;
  i = -1;
  while (env && ++i < length)
    if (i == index)
      {
	if (!(copy[i] = new_var(command)))
	  return (NULL);
      }
    else if (!(copy[i] = copy_varenv(env[i])))
      return (NULL);
  if (env && env[0])
    free_env(env);
  return (copy);
}

static char	**set_new_varenv(char **env, char **command)
{
  char		**copy;
  int		length;
  int		i;

  length = -1;
  if (env)
    while (env[++length]);
  else
    length = 0;
  if (!(copy = malloc(sizeof(char*) * (length + 2))))
    return (NULL);
  copy[length + 1] = NULL;
  i = -1;
  while (++i < length)
    if (!(copy[i] = copy_varenv(env[i])))
      return (NULL);
  if (!(copy[i] = new_var(command)))
    return (NULL);
  if (env && env[0])
    free_env(env);
  return (copy);
}

static char	**add_var_to_env(char **env, char **command)
{
  char		**new_env;
  char		*var;
  int		i;

  if (!(var = malloc(my_strlen(command[1]) + 2)))
    return (NULL);
  i = -1;
  while (command[1][++i] && command[1][i] != '=')
    var[i] = command[1][i];
  var[i] = '=';
  var[++i] = 0;
  i = -1;
  while (env && env[++i] && !my_strcmp(var, env[i]));
  if (!env || !(env[i]))
    {
      if (!(new_env = set_new_varenv(env, command)) && i > -1)
	return (NULL);
    }
  else if (!(new_env = reset_varenv(env, command, i)))
    return (NULL);
  free(var);
  return (new_env);
}

int	setenv_builtin(char ***env, char **command)
{
  char	**new_env;
  int	i;

  i = -1;
  if (my_tablen(command) == 1)
    {
      while (*env && (*env)[++i])
	if (write(1, (*env)[i], my_strlen((*env)[i])) == -1 ||
	    write(1, "\n", 1) == -1)
	  return (-1);
      return (0);
    }
  i = my_tablen(command);
  if (i < 2)
    return (my_int_perror("setenv: Too few arguments.\n", 1));
  else if (i > 3)
    return (my_int_perror("setenv: Too many arguments.\n", 1));
  if (check_varenv_name(command[1]))
    return (1);
  if (!(new_env = add_var_to_env(*env, command)))
    return (-1);
  *env = new_env;
  return (0);
}
