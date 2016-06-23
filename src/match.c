/*
** match.c for match in /home/semmao_i/rendu/PSU_2015_42sh
** 
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
** 
** Started on  Wed Jun  1 18:46:16 2016 ilyas semmaoui
** Last update Wed Jun  1 18:46:52 2016 ilyas semmaoui
*/

int	match(char c, char *str)
{
  int	i;

  i = -1;
  while (str && str[++i])
    if (str[i] == c)
      return (0);
  return (1);
}
