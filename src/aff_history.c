/*
** aff_history.c for 42sh in /home/vigner_g/rendu/prog_shell/PSU_2015_42sh
**
** Made by vigner_g
** Login   <vigner_g@epitech.net>
**
** Started on  Thu Jun  2 11:30:25 2016 vigner_g
** Last update Sun Jun  5 17:31:32 2016 vigner_g
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"mysh.h"

int		ret_history(t_datas *data, t_history *history, char *str)
{
  int		nb;
  int		i;
  t_history	*tmp;

  str += 1;
  i = 0;
  tmp = history;
  if (str != 0)
    {
      nb = my_getnbr(str);
      while (tmp != NULL && i != nb)
	{
	  tmp = tmp->next;
	  i += 1;
	}
      if (i != nb || tmp == NULL)
	return (my_int_perror("Event not found\n", 0));
      if ((execute_command(data, tmp->command)) == -1)
	return (my_int_perror("Failed to exec function\n", -1));
    }
  return (0);
}

int		aff_history(t_history *history)
{
  t_history	*tmp;
  int		i;

  i = 1;
  tmp = history;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  while (tmp != NULL)
    {
      if ((printf("%i %s\n", i, tmp->command)) == -1)
	return (-1);
      tmp = tmp->prev;
      i += 1;
    }
  return (0);
}
