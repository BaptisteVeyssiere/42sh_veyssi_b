/*
** verif_command.c for 42sh in /home/semmao_i/rendu/PSU_2015_42sh
**
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
**
** Started on  Wed Jun  1 18:50:01 2016 ilyas semmaoui
** Last update Thu Jun  9 00:53:49 2016 Baptiste veyssiere
*/

#include "mysh.h"

static int	last_check_value(char *command, t_counter *cnt)
{
  if (cnt->l_red > 1 && cnt->l_arg > 0)
    return (4);
  if (cnt->r_red > 1 && cnt->l_arg > 0)
    return (3);
  if (match(command[cnt->i], "><|&;") == 0)
    cnt->l_arg = 0;
  return (0);
}

static int	verif_count_value(char *command, t_counter *cnt)
{
  if (match(command[cnt->i], "><|& \t;") == 1 &&
      (command[cnt->i + 1] == '\0' ||
       match(command[cnt->i + 1], "><|& \t;") == 0))
    {
      cnt->arg += 1;
      cnt->l_arg += 1;
    }
  if (command[cnt->i] == '>')
    {
      cnt->key = 1;
      if (command[cnt->i + 1] != '>')
	cnt->r_red += 1;
      if (cnt->r_red > 1 && cnt->l_arg == 0)
        return (2);
      cnt->l_arg = 0;
    }
  if (command[cnt->i] == '<')
    {
      if (command[cnt->i + 1] != '<')
	cnt->l_red += 1;
      if (cnt->l_red > 1 && cnt->l_arg == 0)
        return (2);
      cnt->l_arg = 0;
    }
  return (last_check_value(command, cnt));
}

int	change_count_value(char *command, t_counter *cnt)
{
  if (match(command[cnt->i], "|&\t ") == 1)
    cnt->count = 0;
  if (cnt->pipe > 0 && match(command[cnt->i], "|;&") == 0)
    return (1);
  if (match(command[cnt->i], "|\t ") == 1)
    if ((cnt->pipe == 1 && (cnt->l_pipe = 1) == 1) || 1)
      cnt->pipe = 0;
  if (match(command[cnt->i], ";&\t ") == 1)
    cnt->except = 0;
  if ((command[cnt->i] == '|' && command[cnt->i + 1] == '|') ||
      (command[cnt->i] == '&' && command[cnt->i + 1] == '&') ||
      command[cnt->i] == ';')
    {
      if (cnt->l_arg == 0 && cnt->l_red > 0)
        return (2);
      if ((cnt->key = 0) == 0 && ((cnt->l_pipe > 0 && cnt->l_red > 0) ||
				  (cnt->l_red > 1 && cnt->l_arg > 0)))
        return (4);
      cnt->l_red = 0;
      cnt->r_red = 0;
      cnt->l_arg = 0;
      cnt->l_pipe = 0;
    }
  return (verif_count_value(command, cnt));
}

int	check_pipe_and_args(char *command, t_counter *cnt)
{
  if (command[cnt->i] == ';')
    {
      if ((cnt->error == 1 && cnt->arg < 2) ||
          (cnt->arg == 1 && cnt->redir > 0))
        return (1);
      cnt->arg = 0;
      cnt->error = 0;
      cnt->except = 1;
    }
  if (command[cnt->i] == '|' && command[cnt->i - 1] != '|' &&
      command[cnt->i + 1] != '|' && (cnt->l_arg = 0) == 0)
    {
      if ((cnt->error == 1 && cnt->arg < 2) ||
          (cnt->arg == 1 && cnt->redir > 0))
        return (1);
      if (cnt->key == 1 && cnt->arg == 0)
        return (2);
      if ((cnt->arg = 0) == 0 && cnt->key == 1)
        return (3);
      cnt->pipe++;
      cnt->error = 0;
      cnt->l_red = 0;
      cnt->r_red = 0;
    }
  return (0);
}

int	check_redir_and_args(char *command, t_counter *cnt)
{
  if (match(command[cnt->i], "><") == 0)
    {
      if (command[cnt->i] == '<' && cnt->pipe > 0)
        return (4);
      if (cnt->arg == 0)
        cnt->error = 1;
      cnt->redir++;
      if (cnt->redir == 3 ||
          (cnt->redir == 2 && match(command[cnt->i - 1], "\t ") == 0))
        return (2);
    }
  if ((cnt->pipe > 0 && command[cnt->i] == ';') ||
      (cnt->count > 0 && (cnt->pipe > 0 || command[cnt->i] == ';')))
    return (1);
  if ((command[cnt->i] == '|' && command[cnt->i + 1] == '|') ||
      (command[cnt->i] == '&' && command[cnt->i + 1] == '&'))
    {
      cnt->count++;
      if ((cnt->error == 1 && cnt->arg < 2) ||
          (cnt->arg == 1 && cnt->redir > 0))
        return (1);
      cnt->arg = 0;
      cnt->error = 0;
    }
  return (0);
}
