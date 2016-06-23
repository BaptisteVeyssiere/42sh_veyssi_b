/*
** execute_interpipe.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Sun May 29 01:09:08 2016 Baptiste veyssiere
** Last update Sun Jun  5 15:15:48 2016 vigner_g
*/

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static int	pipe_fd(t_command *command, int **fildes, int i)
{
  if (command->command[i]->prev)
    {
      if (dup2(fildes[i - 1][0], 0) == -1)
	return (my_int_perror("Error while using dup2 function.\n", -1));
      if (close(fildes[i - 1][1]) == -1)
	return (-1);
    }
  if (command->command[i]->pipe)
    {
      if (dup2(fildes[i][1], 1) == -1)
        return (my_int_perror("Error while using dup2 function.\n", -1));
    }
  return (0);
}

static int	wait_loop(t_interpipe *command, int *ret, int pid)
{
  int		status;

  if (is_builtin(command, 1) == 1)
    {
      if ((status = check_status(pid, ret)))
	return (status);
    }
  return (0);
}

static int	process_not_builtin(int *pid, t_command *and_or,
				    int **fildes, t_datas *data)
{
  if ((pid[I] = fork()) == -1)
    return (my_int_perror("Error while using fork function.\n", -1));
  if (pid[I] == 0 && pipe_fd(and_or, fildes, I) == -1)
    return (-1);
  if (pid[I] == 0)
    exit(do_instruction(and_or, I, data));
  if ((and_or->command[I]->pipe && close(fildes[I][1]) == -1) ||
      (and_or->command[I]->prev && close(fildes[I - 1][0]) == -1))
    return (my_int_perror("Error while using close function.\n", -1));
  return (0);
}

static int	execute_loop(t_command *and_or,
			     int **fildes, int *pid, t_datas *data)
{
  int		i;
  int		ret;

  ret = 0;
  i = and_or->pipe_nbr + 1;
  if (and_or->pipe_nbr > 0 && pipe(fildes[and_or->pipe_nbr - 1]) == -1)
    return (my_int_perror("Error while using pipe function.\n", -1));
  while (--i >= 0)
    {
      data->tmp = i;
      if (and_or->command[i]->prev && i < and_or->pipe_nbr &&
	  pipe(fildes[i - 1]) == -1)
	return (my_int_perror("Error while using pipe function.\n", -1));
      if (is_builtin(and_or->command[i], 0) == 1)
	  ret = exec_builtins(and_or->command[i]->args, &data->env, data);
      else if (is_builtin(and_or->command[i], 0) != 1)
	if (process_not_builtin(pid, and_or, fildes, data) == -1)
	  return (-1);
    }
  while (++i <= and_or->pipe_nbr)
    if (wait_loop(and_or->command[i], &ret, pid[i]) == -1)
      return (-1);
  return (ret);
}

int	execute_interpipe(t_command *and_or, t_datas *data)
{
  int	i;
  int   **fildes;
  int   *pid;
  int	ret;

  if ((i = -1) == -1 && (((and_or->pipe_nbr &&
        !(fildes = malloc(sizeof(int*) * and_or->pipe_nbr)))) ||
			 !(pid = malloc(sizeof(int) * (and_or->pipe_nbr + 1)))))
    return (-1);
  while (++i < and_or->pipe_nbr)
    if ((fildes[i] = malloc(sizeof(int) * 2)) == NULL)
      return (-1);
  if ((i = -1) == -1 && ((ret = execute_loop(and_or, fildes, pid, data)) == -1
			 || and_or->pipe_nbr))
    {
      while (++i < and_or->pipe_nbr)
        free(fildes[i]);
      if (ret == -1)
	return (free_pid(pid));
      free(fildes);
    }
  free(pid);
  return (ret);
}
