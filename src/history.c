/*
** history.c for 42sh in /home/vigner_g/rendu/prog_shell/PSU_2015_42sh
**
** Made by vigner_g
** Login   <vigner_g@epitech.net>
**
** Started on  Mon May 30 17:11:16 2016 vigner_g
** Last update Sun Jun  5 16:16:34 2016 vigner_g
*/

#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"mysh.h"
#include	"get_next_line.h"
#include	<unistd.h>

int		free_history(t_history *history)
{
  t_history	*tmp;

  while (history != NULL)
    {
      tmp = history;
      if (tmp->command != NULL)
	free(tmp->command);
      history = history->next;
      free(tmp);
    }
  return (0);
}

int		get_file_descriptor(char *home, char *profile, char *type)
{
  int		fd;
  char		*path;

  if ((path = my_malloc(sizeof(char) * (my_strlen(home) + 3 + my_strlen(type) +
					my_strlen(profile))))
      == NULL)
    return (-1);
  my_strcat(path, home);
  my_strcat(path, "/");
  my_strcat(path, type);
  my_strcat(path, "_");
  my_strcat(path, profile);
  if ((fd = open(path, O_RDWR | O_CREAT,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (my_int_perror("get_file_descriptor failed\n", -1));
  free(path);
  return (fd);
}

int		save_in_file(t_datas *data, char *command)
{
  if (data->env != NULL && data->fd != -1 && command[0] != 0 &&
      command[0] != '!')
    {
      if (write(data->fd, command, my_strlen(command)) != my_strlen(command) ||
	  write(data->fd, "\n", 1) != 1)
	return (my_int_perror("save_in_file failed\n", -1));
    }
  return (0);
}

t_history	*add_a_command(t_history *history, char *command)
{
  t_history	*new;

  if (command[0] != 0 && command[0] != '!')
    {
      if ((new = malloc(sizeof(t_history))) == NULL)
	return (NULL);
      new->prev = NULL;
      new->next = history;
      if (history != NULL)
	history->prev = new;
      new->command = command;
      history = new;
    }
  return (history);
}

t_history	*load_history(t_datas *data, char *path,
			      char *profile, t_history *history)
{
  char		*buff;

  if (history != NULL)
    free_history(history);
  if ((data->fd = get_file_descriptor(path, profile, ".42sh_history")) == -1)
    return (NULL);
  history = NULL;
  while ((buff = get_next_line(data->fd)) != NULL)
    if ((history = add_a_command(history, buff)) == NULL)
      return (NULL);
  return (history);
}
