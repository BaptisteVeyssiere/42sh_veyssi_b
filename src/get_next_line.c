/*
** get_next_line.c for get_next_line in /home/VEYSSI_B/rendu/CPE_2015_getnextline/test1
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Mon Jan 11 16:30:41 2016 Baptiste veyssiere
** Last update Thu Jun  9 00:14:05 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "get_next_line.h"

static void	read_loop_bis(int *j, int *end, char *reader)
{
  while (++(*j) < READ_SIZE && *end == 0 && reader[*j] != 0)
    if (reader[*j] == '\n')
      *end = 1;
}

static char	*my_realloc(char *ptr, int size)
{
  char		*tmp;
  int		i;

  tmp = NULL;
  i = -1;
  if ((tmp = malloc(sizeof(char*) * size)) == NULL)
    return (NULL);
  while (++i < size)
    tmp[i] = 0;
  i = -1;
  while (ptr[++i] != 0 && i < size)
    tmp[i] = ptr[i];
  while (++i <= size)
    tmp[i] = 0;
  free(ptr);
  ptr = NULL;
  ptr = tmp;
  return (ptr);
}

static char	*init(char *buffer, char *line,
		      int *static_counter, int *line_index)
{
  int		i;
  int		j;

  if (buffer[0] == 0)
    i = READ_SIZE;
  else
    i = READ_SIZE + my_strlen(buffer);
  if ((line = malloc(sizeof(char*) * i)) == NULL)
    return (NULL);
  j = -1;
  while (++j <= i)
    line[j] = 0;
  if (buffer[*static_counter] == '\n')
    ++(*static_counter);
  while (buffer[*static_counter] != '\n' && buffer[*static_counter] != 0
	 && *static_counter < READ_SIZE)
    line[++(*line_index)] = buffer[(*static_counter)++];
  if (buffer[*static_counter] == 0)
    {
      i = -1;
      while (++i <= READ_SIZE)
        buffer[i] = 0;
      *static_counter = 0;
    }
  return (line);
}

static char	*read_loop(char *line, int fd, int line_index, char *buffer)
{
  int		end;
  int		i;
  int		j;
  char		reader[READ_SIZE + 1];

  end = 0;
  while ((j = -1) == -1 && end == 0)
    {
      while (++j <= READ_SIZE)
	reader[j] = 0;
      end = (read(fd, reader, READ_SIZE) < READ_SIZE) ? (1) : (0);
      if ((i = -1) == -1 && end == 1 && reader[0] == 0 && line[0] == 0)
        return (free_line(line, NULL));
      while (++i < READ_SIZE && reader[i] != '\n' && reader[i] != 0)
	line[++line_index] = reader[i];
      if ((j = -1) == -1 && end == 0 && reader[i] == 0)
	if ((line = my_realloc(line, (my_strlen(line) + READ_SIZE))) == NULL)
	  return (NULL);
      if (reader[i] == '\n' && READ_SIZE > 1)
	--i;
      read_loop_bis(&j, &end, reader);
    }
  while (++i < READ_SIZE)
    buffer[++j] = reader[i];
  return (line);
}

char		*get_next_line(const int fd)
{
  char		*line;
  static char	buffer[READ_SIZE + 1] = {0};
  static int	static_counter = 0;
  int		line_index;

  line = NULL;
  line_index = -1;
  if ((line = init(buffer, line, &static_counter, &line_index)) == NULL)
    return (NULL);
  if (buffer[static_counter] != '\n')
    if ((line = read_loop(line, fd, line_index, buffer)) == NULL)
      return (NULL);
  return (line);
}
