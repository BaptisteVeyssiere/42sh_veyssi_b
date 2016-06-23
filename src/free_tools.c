/*
** free_tools.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 17:30:53 2016 Baptiste veyssiere
** Last update Sun Jun  5 17:42:47 2016 Nathan Scutari
*/

#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"

void	free_tab(char **tab)
{
  int	i;

  i = -1;
  if (tab == NULL)
    return ;
  while (tab[++i])
    if (tab[i])
      free(tab[i]);
  free(tab);
}

static void	free_tree_leaves(t_interpipe *command)
{
  if (command->output_file)
    free(command->output_file);
  if (command->input_file)
    free(command->input_file);
  free(command->str);
  free_tab(command->args);
  free(command);
}

void	free_tree(t_tree **tree)
{
  int	i;
  int	j;
  int	k;

  i = -1;
  while (tree[++i])
    {
      j = -1;
      while (tree[i]->and_or[++j])
	{
	  k = -1;
	  while (tree[i]->and_or[j]->command[++k])
	    free_tree_leaves(tree[i]->and_or[j]->command[k]);
	  free(tree[i]->and_or[j]->command);
	  free(tree[i]->and_or[j]);
	}
      free(tree[i]->and_or);
      free(tree[i]);
    }
  free(tree);
}

int	free_pid(int *pid)
{
  free(pid);
  return (-1);
}

void	free_all(t_datas *data, char **prompt)
{
  free_prompt(prompt);
  free_alias(data->alias);
  free_history(data->history);
  close(data->fd);
  free(data->home);
  free_env(data->env);
}
