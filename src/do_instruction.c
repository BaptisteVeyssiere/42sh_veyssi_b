/*
** do_instruction.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Sun May 29 01:43:17 2016 Baptiste veyssiere
** Last update Thu Jun  9 00:36:08 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "mysh.h"

static int	change_fd_on(int *fd_input, int *fd_output,
			     t_command *command, int i)
{
  if (command->command[i]->fd_input != 0)
    {
      if ((*fd_input = dup(0)) == -1 || close(0) == -1 ||
          dup(command->command[i]->fd_input) == -1)
	return (-1);
    }
  if (command->command[i]->fd_output != 1)
    {
      if ((*fd_output = dup(1)) == -1 ||
          close(1) == -1 ||
          dup(command->command[i]->fd_output)  == -1)
        return (-1);
    }
  if (*fd_input == -1 || *fd_output == -1)
    return (-1);
  return (0);
}

static int	exec_instruction(char if_builtin,
				 t_interpipe *command, t_datas *data)
{
  int		ret;

  if (if_builtin)
    {
	if ((ret = exec_builtins(command->args, &data->env, data)))
	  return (ret);
      exit (EXIT_SUCCESS);
    }
  else if (execve(command->args[0],
		  command->args, data->env) == -1)
    {
      if (my_int_perror(command->args[0], 0) ||
	  my_int_perror(": Exec format error. Binary file not executable.\n", 0))
	exit(-1);
      exit(1);
    }
  return (EXIT_SUCCESS);
}

int	do_instruction(t_command *and_or, int i, t_datas *data)
{
  char  builtin;
  int   fd_input;
  int   fd_output;

  fd_input = -2;
  fd_output = -2;
  if (and_or->command[i]->if_double_left)
    if (double_left_red(and_or->command[i]) == -1)
      return (-1);
  if (change_fd_on(&fd_input, &fd_output, and_or, i) == -1)
    return (-1);
  builtin = 0;
  if (my_strcmp_strict(and_or->command[i]->args[0], "env") ||
      my_strcmp_strict(and_or->command[i]->args[0], "echo") ||
      (my_strcmp_strict(and_or->command[i]->args[0], "setenv") &&
       !(and_or->command[i]->args[1])))
    builtin = 1;
  return (exec_instruction(builtin, and_or->command[i], data));
}
