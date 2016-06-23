/*
** get_command_tree.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 23:29:21 2016 Baptiste veyssiere
** Last update Sat May 28 01:03:25 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

t_interpipe	*get_command_tree(char *command)
{
  t_interpipe	*interpipe;
  int		length;

  if (!(interpipe = malloc(sizeof(t_interpipe))))
    return (NULL);
  interpipe->fd_input = 0;
  interpipe->fd_output = 1;
  interpipe->left_red = 0;
  interpipe->right_red = 0;
  interpipe->input_file = NULL;
  interpipe->output_file = NULL;
  interpipe->if_double_left = 0;
  interpipe->if_double_right = 0;
  interpipe->pipe = 0;
  interpipe->prev = 0;
  interpipe->str = 0;
  interpipe->args = NULL;
  length = my_strlen(command);
  if (!(interpipe->str = malloc(length + 1)))
    return (NULL);
  interpipe->str[length] = 0;
  my_strcpy(command, interpipe->str);
  return (interpipe);
}
