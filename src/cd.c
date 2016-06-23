/*
** cd.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed Mar 30 16:41:56 2016 Baptiste veyssiere
** Last update Tue May 31 20:01:42 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

static int	cd_setenv(char ***env, char *var, char *value)
{
  char		**tab;

  if ((tab = malloc(sizeof(char*) * 4)) == NULL ||
      (tab[0] = malloc(sizeof(char) * (my_strlen("setenv") + 1))) == NULL ||
      (tab[1] = malloc(sizeof(char) * (my_strlen(var) + 1))) == NULL ||
      (tab[2] = malloc(sizeof(char) * (my_strlen(value) + 1))) == NULL)
    return (-1);
  tab[3] = NULL;
  my_strcpy("setenv", tab[0]);
  my_strcpy(var, tab[1]);
  my_strcpy(value, tab[2]);
  if (setenv_builtin(env, tab) == -1)
    return (-1);
  free_tab(tab);
  return (0);
}

static int	cd_home(char ***env)
{
  char		*home;
  char		*pwd;

  if ((home = get_varenv(*env, "HOME")) == NULL ||
      (pwd = get_varenv(*env, "PWD")) == NULL)
    return (-1);
  if (chdir(home) == -1)
    return (-1);
  if (cd_setenv(env, "OLDPWD", pwd) == -1 ||
      cd_setenv(env, "PWD", home) == -1)
    return (-1);
  free(pwd);
  free(home);
  return (0);
}

static int	cd_prev(char ***env, char **oldpwd)
{
  char		*pwd;
  char		*buf;

  buf = NULL;
  if ((pwd = getcwd(buf, 100)) == NULL)
    return (-1);
  if (chdir(*oldpwd) == -1)
    return (-1);
  if (cd_setenv(env, "OLDPWD", pwd) == -1 ||
      cd_setenv(env, "PWD", *oldpwd) == -1)
    return (-1);
  free(*oldpwd);
  *oldpwd = pwd;
  return (0);
}

static int	cd_basic(char **command, char ***env)
{
  char		*pwd;
  char		*buf;

  buf = NULL;
  if ((pwd = getcwd(buf, 100)) == NULL)
    return (-1);
  if (check_if_exist(command[1]))
    return (1);
  if (chdir(command[1]) == -1)
    return (-1);
  buf = NULL;
  if (cd_setenv(env, "OLDPWD", pwd) == -1 ||
      cd_setenv(env, "PWD", getcwd(buf, 100)) == -1)
    return (-1);
  free(buf);
  free(pwd);
  return (0);
}

int		cd_builtin(char ***env, char **command)
{
  static char	*oldpwd = NULL;
  char		*buf;

  buf = NULL;
  if (!command[1] || my_strcmp_strict("~", command[1]))
    {
      if (!(oldpwd = getcwd(buf, 100)) ||
	  cd_home(env))
	return (-1);
    }
  else if (my_strcmp_strict("-", command[1]))
    {
      if (cd_prev(env, &oldpwd))
	return (-1);
    }
  else if (!(oldpwd = getcwd(buf, 100)) ||
	   cd_basic(command, env))
    return (1);
  return (0);
}
