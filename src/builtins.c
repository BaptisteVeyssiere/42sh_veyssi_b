/*
** builtins.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Sun May 29 02:01:39 2016 Baptiste veyssiere
** Last update Sun Jun  5 02:17:00 2016 Nathan Scutari
*/

#include	<unistd.h>
#include	<string.h>
#include	"mysh.h"

static int	check_mode_a(t_interpipe *command)
{
  if (my_strcmp_strict(command->args[0], "cd") ||
      my_strcmp_strict(command->args[0], "exit") ||
      my_strcmp_strict(command->args[0], "profile") ||
      my_strcmp_strict(command->args[0], "history") ||
      my_strcmp_strict(command->args[0], "source") ||
      (strncmp(command->args[0], "!", 1)) == 0 ||
      (my_strcmp_strict(command->args[0], "setenv") &&
       command->args[1]) ||
      my_strcmp_strict(command->args[0], "unsetenv"))
    return (1);
  return (0);
}

static int	check_mode_b(t_interpipe *command)
{
  if (!my_strcmp_strict(command->args[0], "cd") &&
      !my_strcmp_strict(command->args[0], "exit") &&
      !my_strcmp_strict(command->args[0], "profile") &&
      !my_strcmp_strict(command->args[0], "history") &&
      !my_strcmp_strict(command->args[0], "source") &&
      (strncmp(command->args[0], "!", 1)) != 0 &&
      (!my_strcmp_strict(command->args[0], "setenv") ||
       (my_strcmp_strict(command->args[0], "setenv") && !(command->args[1]))) &&
      !my_strcmp_strict(command->args[0], "unsetenv"))
    return (1);
  return (0);
}

int		is_builtin(t_interpipe *command, int mode)
{
  if (mode == 0)
    {
      if (check_mode_a(command) == 1)
	return (1);
    }
  else if (mode == 1)
    {
      if (check_mode_b(command) == 1)
	return (1);
    }
  return (0);
}

static void	create_func_ptr(int (*ptr[7])(char***, char**))
{
  ptr[0] = &(cd_builtin);
  ptr[1] = &(env_builtin);
  ptr[2] = &(setenv_builtin);
  ptr[3] = &(unsetenv_builtin);
  ptr[4] = &(exit_builtin);
  ptr[5] = &(echo_builtin);
  ptr[6] = NULL;
}

int		exec_builtins(char **args, char ***env, t_datas *data)
{
  int	(*ptr[7])(char***, char**);
  char	*name[7];
  int	i;

  name[0] = "cd";
  name[1] = "env";
  name[2] = "setenv";
  name[3] = "unsetenv";
  name[4] = "exit";
  name[5] = "echo";
  create_func_ptr(ptr);
  i = -1;
  if (args[0] != NULL && data->fd != -1 && my_strcmp_strict(args[0], "profile"))
    profile(args, data);
  else if (args[0] != NULL && my_strcmp_strict(args[0], "source"))
    data->alias = load_alias(args[1], *env, data->alias);
  else if (args[0] != NULL && my_strcmp_strict(args[0], "history"))
    aff_history(data->history);
  else if (args[0] != NULL && strncmp(args[0], "!", 1) == 0)
    ret_history(data, data->history, args[0]);
  while (++i < 6 && !my_strcmp_strict(name[i], args[0]));
  if (i == 6)
    return (1);
  else
    return (ptr[i](env, args));
}
