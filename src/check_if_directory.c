/*
** check_if_directory.c for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Mon May 30 23:49:50 2016 Baptiste veyssiere
** Last update Sun Jun  5 00:39:54 2016 Baptiste veyssiere
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mysh.h"

int		check_if_directory(char *command)
{
  struct stat	buf;

  if (command[0] != '/')
    return (0);
  if (access(command, F_OK) == 0 &&
      stat(command, &buf) == -1)
    return (-1);
  if (S_ISDIR(buf.st_mode))
    {
      if (write(2, command, my_strlen(command)) == -1)
	return (-1);
      return (my_int_perror(": Permission denied.\n", 1));
    }
  return (0);
}

int		check_if_exist(char *command)
{
  struct stat	buf;

  if (access(command, F_OK))
    {
      if (write(2, command, my_strlen(command)) == -1)
	return (-1);
      return (my_int_perror(": No such file or directory.\n", 1));
    }
  if (stat(command, &buf) == -1)
    return (-1);
  if ((S_IRUSR & buf.st_mode) == 0)
    {
      if (write(2, command, my_strlen(command)) == -1)
        return (-1);
      return (my_int_perror(": Permission denied.\n", 1));
    }
  if (S_ISDIR(buf.st_mode) == 0)
    {
      if (write(2, command, my_strlen(command)) == -1)
        return (-1);
      return (my_int_perror(": Not a directory.\n", 1));
    }
  return (0);
}

int	check_exit(t_tree **tree)
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
	  while (tree[i]->and_or[j]->command[++k]);
	  --k;
	  if (tree[i]->and_or[j]->command[k]->args[0] &&
	      my_strcmp_strict(tree[i]->and_or[j]->command[k]->args[0], "exit"))
	    {
	      if (write(1, "exit\n", 5) == -1)
		return (1);
	      return (1);
	    }
	}
    }
  return (0);
}

int	check_varenv_name(char *name)
{
  int	i;

  i = -1;
  if (name[0] < 'A' ||
      (name[0] > 'Z' && name[0] < 'a') ||
      name[0] > 'z')
    {
      if (my_int_perror("setenv: Variable name must begin", 0))
	return (-1);
      return (my_int_perror(" with a letter.\n", 1));
    }
  while (name[++i])
    if (name[i] < '0' ||
	(name[i] > '9' && name[i] < 'A') ||
	(name[i] > 'Z' && name[i] < 'a') ||
	name[i] > 'z')
      {
	if (my_int_perror("setenv: Variable name must contain", 0))
	  return (-1);
	return (my_int_perror(" alphanumeric characters.\n", 1));
      }
  return (0);
}

int		check_permission(char *file, char permission)
{
  struct stat	buf;
  int		check;

  if (check_dir_permission(file, permission))
    return (1);
  if (access(file, F_OK))
    return (0);
  if (stat(file, &buf) == -1)
    return (-1);
  if (permission == 'r')
    check = (S_IRUSR & buf.st_mode);
  else if (permission == 'w')
    check = (S_IWUSR & buf.st_mode);
  else if (permission == 'x')
    check = (S_IXUSR & buf.st_mode);
  if (!check || (permission == 'w' && !(S_IWUSR & buf.st_mode)))
    {
      if (write(2, file, my_strlen(file)) == -1)
        return (-1);
      return (my_int_perror(": Permission denied.\n", 1));
    }
  return (0);
}
