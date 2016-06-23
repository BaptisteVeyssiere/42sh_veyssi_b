/*
** double_left_red.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Sun Apr 10 00:49:54 2016 Baptiste veyssiere
** Last update Thu Jun  9 00:34:25 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mysh.h"
#include "get_next_line.h"

static int	fill_file(int fd, char *end)
{
  char		*str;

  while ((str = get_next_line(0)) != NULL &&
	 my_strcmp_strict(str, end) == 0)
    {
      if (write(fd, str, my_strlen(str)) == -1 ||
	  write(fd, "\n", 1) == -1)
	return (-1);
      free(str);
    }
  return (0);
}

int	double_left_red(t_interpipe *command)
{
  int		fd;
  mode_t	mode;

  mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  if ((fd = open("/tmp/mysh", O_CREAT | O_TRUNC | O_WRONLY, mode)) == -1)
    return (-1);
  if (fill_file(fd, command->input_file) == -1 ||
      close(fd) == -1)
    return (-1);
  if ((fd = open("/tmp/mysh", O_RDONLY)) == -1)
    return (-1);
  command->fd_input = fd;
  return (0);
}
