/*
** check_and_add_path.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Sat May 28 21:38:00 2016 Baptiste veyssiere
** Last update Sun Jun  5 02:30:33 2016 Nathan Scutari
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysh.h"

static int	check_if_builtin(char *command)
{
  if (my_strcmp_strict(command, "env") == 1 ||
      my_strcmp_strict(command, "setenv") == 1 ||
      my_strcmp_strict(command, "unsetenv") == 1 ||
      my_strcmp_strict(command, "echo") == 1 ||
      my_strcmp_strict(command, "exit") == 1 ||
      my_strcmp_strict(command, "cd") == 1 ||
      my_strcmp_strict(command, "profile") == 1 ||
      my_strcmp_strict(command, "source") == 1 ||
      my_strcmp_strict(command, "history") == 1 ||
      (strncmp(command, "!", 1)) == 0)
    return (0);
  return (1);
}

static char	*add_testpath(char *copy, char *tabi)
{
  char		*str;
  int		i;
  int		j;

  if ((str = malloc(sizeof(char) *
                    (my_strlen(copy) + my_strlen(tabi) + 1))) == NULL)
    return (NULL);
  i = -1;
  while (tabi[++i])
    str[i] = tabi[i];
  j = -1;
  --i;
  while (copy[++j])
    str[++i] = copy[j];
  str[++i] = 0;
  return (str);
}

static int	test_path(char **tab, char **command)
{
  int		i;
  char		*copy;

  if (slash_test(*command) == 1)
    {
      if (access(command[0], F_OK))
	return (1);
      else
	return (0);
    }
  i = -1;
  while (tab[++i])
    {
      if (!(copy = add_testpath(*command, tab[i])))
        return (-1);
      if (access(copy, F_OK) == 0)
        {
          free(*command);
	  *command = copy;
          return (0);
        }
      free(copy);
    }
  return (1);
}

static int	add_path(char **command, char **env)
{
  char		*path;
  char		**tab;
  int		ret;

  if (env == NULL || (path = get_varenv(env, "PATH")) == NULL)
    {
      path = NULL;
      if (!(path = malloc(my_strlen("/bin") + 1)))
        return (-1);
      path[my_strlen("/bin")] = 0;
      my_strcpy("/bin", path);
    }
  if ((tab = get_varpath(path)) == NULL)
    return (-1);
  ret = test_path(tab, command);
  free_tab(tab);
  free(path);
  return (ret);
}

int	check_and_add_path(t_interpipe **command, char **env)
{
  int	i;
  int	ret;

  i = -1;
  while (command[++i] && command[i]->args[0])
    {
      if (command[i]->args[0][0] == '.' &&
	  (!command[i]->args[0][1] ||
	   (command[i]->args[0][1] == '.' && !command[i]->args[0][2])))
	return (1);
      if ((ret = check_if_directory(command[i]->args[0])))
	return (ret);
      ret = check_if_builtin(command[i]->args[0]);
      if (ret && (ret = add_path(&(command[i]->args[0]), env)))
	{
	  if (ret && command_not_found(command[i]->args[0]) == -1)
	    return (-1);
	  return (ret);
	}
      if (check_permission(command[i]->args[0], 'x'))
	return (1);
    }
  return (0);
}
