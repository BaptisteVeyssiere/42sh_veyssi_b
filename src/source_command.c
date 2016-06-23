/*
** source_command.c for sh in /home/scutar_n/rendu/PSU/PSU_2015_42sh/src
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Sun Jun  5 03:12:05 2016 Nathan Scutari
** Last update Sun Jun  5 22:32:48 2016 Nathan Scutari
*/

#include <stdlib.h>
#include <mysh.h>

static char	*get_a_word(char *str, int *x)
{
  int	save;
  char	*word;
  int	y;
  int	i;

  i = *x - 1;
  save = *x;
  while (str[++i] && str[i] != ' ' && str[i] != ';' && str[i] != '\t' &&
	 str[i] != '|' && str[i] != '&');
  if ((word = malloc(i - save + 1)) == NULL)
    return (NULL);
  save -= 1;
  y = -1;
  while (++save < i)
    word[++y] = str[save];
  word[++y] = 0;
  *x = i - 1;
  return (word);
}

static int	is_alias(char **word, t_alias *alias)
{
  while (alias != NULL)
    {
      if (my_strcmp_strict(*word, alias->alias))
	{
	  free(*word);
	  *word = alias->equivalent;
	  return (1);
	}
      alias = alias->next;
    }
  return (0);
}

static char	*replace_word(char *word, char *str, int save, int *i)
{
  char	*new_str;
  int	x;
  int	y;

  x = -1;
  if ((new_str = malloc(my_strlen(word) - alias_length(&str[save])
			+ 3 + my_strlen(str))) == NULL)
    return (NULL);
  while (++x < save)
    new_str[x] = str[x];
  new_str[x] = ' ';
  y = -1;
  while (word[++y])
    new_str[++x] = word[y];
  new_str[++x] = ' ';
  *i = x;
  save += alias_length(&str[save]) - 1;
  while (str[++save])
    new_str[++x] = str[save];
  new_str[++x] = 0;
  free(str);
  return (new_str);
}

char	*replace_by_alias(char *str, t_alias *list)
{
  char	*new_str;
  char	*word;
  int	save;
  int	x;

  x = -1;
  if ((new_str = copy_str(str)) == NULL)
    return (NULL);
  while (new_str[++x])
    {
      if (new_str[x] != ';' && new_str[x] != ' ' && new_str[x] != '\t' &&
	  new_str[x] != '|' && new_str[x] != '&')
	{
	  save = x;
	  if ((word = get_a_word(new_str, &x)) && is_alias(&word, list))
	    {
	      if ((new_str = replace_word(word, new_str, save, &x)) == NULL)
		return (NULL);
	    }
	  else if (word)
	    free(word);
	}
    }
  return (new_str);
}
