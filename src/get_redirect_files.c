/*
** get_redirect_files.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Sat May 28 00:11:16 2016 Baptiste veyssiere
** Last update Sat Jun  4 17:12:09 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static void	get_redirect_type(t_interpipe *interpipe, char *command)
{
  int		i;

  i = -1;
  while (command[++i] && command[i] != '>' && command[i] != '<');
  if (!command[i])
    return ;
  if (command[i] == '>' && command[i + 1] == '>')
    interpipe->if_double_right = 1;
  else if (command[i] == '>' && command[i + 1] != '>')
    interpipe->right_red = 1;
  else if (command[i] == '<' && command[i + 1] == '<')
    interpipe->if_double_left = 1;
  else if (command[i] == '<' && command[i + 1] != '<')
    interpipe->left_red = 1;
}

static int	get_redirect_length(char *str, int i)
{
  int		length;

  length = 0;
  while (str[++i] && str[i] != ' ')
    ++length;
  return (length);
}

char	*get_redirect_name(char *str, char mode)
{
  int	i;
  int	j;
  int	length;
  char	*name;

  i = -1;
  while (str[++i] && str[i] != mode);
  --i;
  while (str[++i] && (str[i] == mode || str[i] == ' '))
    str[i] = ' ';
  --i;
  length = get_redirect_length(str, i);
  if (!(name = malloc(length + 1)))
    return (NULL);
  name[length] = 0;
  j = -1;
  while (++j < length)
    {
      name[j] = str[++i];
      str[i] = ' ';
    }
  return (name);
}

int	get_redirect_files(t_interpipe *interpipe, char *command)
{
  get_redirect_type(interpipe, command);
  if (((interpipe->left_red || interpipe->if_double_left) &&
       !(interpipe->input_file = get_redirect_name(command, '<'))) ||
      ((interpipe->right_red || interpipe->if_double_right) &&
       !(interpipe->output_file = get_redirect_name(command, '>'))))
    return (-1);
  get_redirect_type(interpipe, command);
  if ((interpipe->input_file == NULL &&
       (interpipe->left_red || interpipe->if_double_left) &&
       !(interpipe->input_file = get_redirect_name(command, '<'))) ||
      (interpipe->output_file == NULL &&
       (interpipe->right_red || interpipe->if_double_right) &&
       !(interpipe->output_file = get_redirect_name(command, '>'))))
    return (-1);
  return (0);
}
