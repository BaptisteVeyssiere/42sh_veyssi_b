/*
** slash_test.c for mysh in /home/VEYSSI_B/rendu/Programmation_Shell/PSU_2015_minishell2/test
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Sat Apr  9 15:38:42 2016 Baptiste veyssiere
** Last update Sat Apr  9 23:56:29 2016 Baptiste veyssiere
*/

int	slash_test(char *command)
{
  int   i;

  i = -1;
  while (command[++i])
    if (command[i] == '/')
      return (1);
  return (0);
}
