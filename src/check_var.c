/*
** check_var.c for 42 in /home/semmao_i/rendu/PSU_2015_42sh/src
**
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
**
** Started on  Thu Jun  2 10:47:20 2016 ilyas semmaoui
** Last update Sat Jun  4 17:00:58 2016 Baptiste veyssiere
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

static char	*my_realloc(char *str1, char *str2)
{
  int		i;
  int		j;
  int		len;
  int		size;
  char		*new;

  len = my_strlen(str2);
  size = my_strlen(str1);
  i = -1;
  if ((new = malloc(sizeof(char) * (len + size + 2))) == NULL)
    return (NULL);
  while (str2[++i])
    new[i] = str2[i];
  j = i;
  new[i] = str1[i - j];
  while (str1 && str1[++i - j])
    new[i] = str1[i - j];
  new[i] = '\0';
  free(str2);
  free(str1);
  return (new);
}

static int	check_last_value(char **env, t_var *var, int last_value)
{
  if (my_strcmp_strict(var->tmp, "?") == 1)
    {
      if ((var->var = my_getstr(last_value)) == NULL)
	return (-1);
    }
  else if (--var->n && (var->var = get_varenv(env, var->tmp)) == NULL)
    {
      if (write(2, var->tmp, my_strlen(var->tmp)) == -1 ||
	  write(2, ": Undefined variable.\n", 22) == -1)
	return (-1);
      free(var->tmp);
      free(var->command);
      return (-1);
    }
  return (0);
}

static int	swap_var(char **line, char **env, t_var *var, int last_value)
{
  var->start = var->i;
  while ((*line)[++var->i] && (*line)[var->i] != '$');
  if ((var->n = var->start) == var->start && var->i - var->start < 2)
    {
      free(var->command);
      return (-1);
    }
  if (--var->i && (var->tmp = malloc(var->i - var->start + 1)) == NULL)
    return (-1);
  while ((*line)[++var->n] && (*line)[var->n] != '$')
    var->tmp[var->n - (var->start + 1)] = (*line)[var->n];
  var->tmp[var->n - (var->start + 1)] = '\0';
  if (check_last_value(env, var, last_value) == -1)
    return (-1);
  free(var->tmp);
  if ((var->command = my_realloc(var->command, var->var)) == NULL)
    return (-1);
  return (0);
}

static int	change_var(char **line, char **env, int last_value)
{
  t_var		var;

  var.i = -1;
  var.n = -1;
  if ((var.command = malloc(my_strlen(*line) + 1)) == NULL)
    return (-1);
  while (++var.i <= my_strlen(*line))
    var.command[var.i] = 0;
  var.i = -1;
  while (*line && (*line)[++var.i])
    {
      if ((*line)[var.i] == '$')
	{
	  if (swap_var(line, env, &var, last_value) == -1)
	    return (-1);
	}
      else
	{
	  var.command[++var.n] = (*line)[var.i];
	  var.command[var.n + 1] = '\0';
	}
    }
  free(*line);
  *line = var.command;
  return (0);
}

int	check_var(t_interpipe **command, char **env, int last_value)
{
  int	i;
  int	j;

  i = -1;
  while (command && command[++i] != NULL)
    {
      j = -1;
      while (command[i]->args && command[i]->args[++j])
	if (change_var(&(command[i]->args[j]), env, last_value) == -1)
	  return (-1);
    }
  return (0);
}
