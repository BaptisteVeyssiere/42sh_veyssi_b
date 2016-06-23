/*
** fill_leaf.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Fri May 27 15:27:38 2016 Baptiste veyssiere
** Last update Sat May 28 21:25:58 2016 Baptiste veyssiere
*/

#include <mysh.h>

int	fill_leaf(t_tree **tree)
{
  int	i;
  int	j;
  int	k;

  i = -1;
  while (tree[++i])
    {
      j = -1;
      while (tree[i]->and_or[++j] && (k = -1) == -1)
	while (tree[i]->and_or[j]->command[++k])
	  {
	    if (k > 0)
	      tree[i]->and_or[j]->command[k]->prev = 1;
	    if (tree[i]->and_or[j]->command[k + 1])
	      tree[i]->and_or[j]->command[k]->pipe = 1;
	    if (get_redirect_files(tree[i]->and_or[j]->command[k],
				   tree[i]->and_or[j]->command[k]->str) ||
		!(tree[i]->and_or[j]->command[k]->args =
		  str_to_wordtab(tree[i]->and_or[j]->command[k]->str)))
	      return (-1);
	  }
    }
  return (0);
}
