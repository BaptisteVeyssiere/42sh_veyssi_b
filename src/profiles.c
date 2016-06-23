/*
** profiles.c for 42sh in /home/vigner_g/rendu/prog_shell/PSU_2015_42sh
**
** Made by vigner_g
** Login   <vigner_g@epitech.net>
**
** Started on  Tue May 31 22:54:40 2016 vigner_g
** Last update Wed Jun  1 18:33:22 2016 vigner_g
*/

#include	<stdlib.h>
#include	"mysh.h"

int		profile(char **seq, t_datas *data)
{
  if (seq[1] != NULL)
    data->history = load_history(data, data->home,
				 seq[1], data->history);
  return (0);
}
