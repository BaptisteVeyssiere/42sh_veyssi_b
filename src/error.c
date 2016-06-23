/*
** error.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 17:28:25 2016 Baptiste veyssiere
** Last update Sat May 28 22:42:43 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include "mysh.h"

int	my_int_perror(char *str, int ret)
{
  if (write(2, str, my_strlen(str)) == -1)
    return (-1);
  return (ret);
}

char	*my_char_perror(char *str)
{
  if (write(2, str, my_strlen(str)) == -1)
    return (NULL);
  return (NULL);
}

int	command_not_found(char *command)
{
  if (write(2, command, my_strlen(command)) == -1 ||
      write(2, ": Command not found.\n", 21) == -1)
    return (-1);
  return (0);
}
