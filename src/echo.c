/*
** echo.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Mon May 30 01:16:00 2016 Baptiste veyssiere
** Last update Tue May 31 00:21:59 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include "mysh.h"

int	echo_builtin(UNUSED char ***env, char **command)
{
  char	end;
  int	i;

  end = 0;
  i = 0;
  if (command[1] && my_strcmp_strict(command[1], "-n"))
    end = 1;
  i += end;
  while (command[++i])
    if (write(1, command[i], my_strlen(command[i])) == -1 ||
	(command[i + 1] && write(1, " ", 1) == -1))
      return (-1);
  if (!end && write(1, "\n", 1) == -1)
    return (1);
  return (0);
}
