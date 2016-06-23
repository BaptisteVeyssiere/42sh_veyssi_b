/*
** main.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 17:14:35 2016 Baptiste veyssiere
** Last update Thu Jun  9 00:24:46 2016 Baptiste veyssiere
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"mysh.h"
#include	"get_next_line.h"

int		ctrc = 0;

void		handler(UNUSED int sign)
{
  ctrc = 1;
  if (signal(SIGINT, &handler) == SIG_ERR ||
      write(1, "\n", 1) == -1)
    return ;
}

static int	clone_env(char **env_tmp, t_datas *data)
{
  char		**env;

  if ((env = env_copy(env_tmp)) == NULL && env_tmp[0] != NULL)
    return (-1);
  data->env = env;
  data->fd = -1;
  return (0);
}

static int	loading_data(t_datas *data, char **env_tmp, char ***prompt)
{
  data->history = NULL;
  data->alias = load_alias(NULL, env_tmp, NULL);
  if (clone_env(env_tmp, data) == -1 || (*prompt = get_prompt()) == NULL ||
      aff_prompt(*prompt) == -1)
      return (-1);
  if ((data->home = get_varenv(env_tmp, "HOME")) != NULL)
    data->history = load_history(data, data->home,
				 "default", data->history);
  return (0);
}

static int	my_shell(char **env_tmp)
{
  char		*command;
  char		**prompt;
  t_datas	data;
  int		ret;

  if (loading_data(&data, env_tmp, &prompt) == -1)
    return (-1);
  ret = 0;
  if (signal(SIGINT, &handler) == SIG_ERR)
    return (-1);
  while ((command = get_next_line(0)) || (command == NULL && ctrc == 1))
    {
      ctrc = 0;
      if (command && (ret = execute_command(&data, command)) == -1 && ctrc == 0)
	return (-1);
      free(command);
      free_prompt(prompt);
      if (!(prompt = get_prompt()) || aff_prompt(prompt) == -1)
	return (-1);
      ctrc = 0;
    }
  free_all(&data, prompt);
  return (ret);
}

int		main(int ac, UNUSED char **av, char **env)
{
  if (ac != 1)
    return (EXIT_SUCCESS);
  return (my_shell(env));
}
