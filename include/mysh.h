/*
** mysh.h for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Wed May 25 17:19:37 2016 Baptiste veyssiere
** Last update Sun Jun  5 22:44:11 2016 Baptiste veyssiere
*/

#ifndef MYSH_H_
# define MYSH_H_

# define UNUSED __attribute__((unused))
# define I data->tmp

# ifndef WCOREDUMP
#  define WCOREDUMP(status) ((status) & 0x80)
# endif /* !WCOREDUMP */

typedef struct		s_var
{
  char			*command;
  char			*tmp;
  char			*var;
  int			i;
  int			n;
  int			start;
}			t_var;

typedef struct		s_counter
{
  int			i;
  int			redir;
  int			l_red;
  int			r_red;
  int			count;
  int			pipe;
  int			l_pipe;
  int			key;
  int			arg;
  int			l_arg;
  int			except;
  int			error;
}			t_counter;

typedef struct		s_interpipe
{
  int			fd_input;
  char			*input_file;
  int			fd_output;
  char			*output_file;
  char			left_red;
  char			right_red;
  char			if_double_left;
  char			if_double_right;
  char			pipe;
  char			prev;
  char			*str;
  char			**args;
}			t_interpipe;

typedef struct		s_command
{
  int			pipe_nbr;
  char			and;
  char			or;
  t_interpipe		**command;
}			t_command;

typedef struct		s_history
{
  char			*command;
  struct s_history	*next;
  struct s_history	*prev;
}			t_history;

typedef struct		s_alias
{
  int			source;
  char			*alias;
  char			*equivalent;
  struct s_alias        *next;
}			t_alias;

typedef struct		s_datas
{
  char			*home;
  char			*profile;
  char			**env;
  int			fd;
  t_history		*history;
  int			tmp;
  t_alias		*alias;
}			t_datas;

typedef struct		s_tree
{
  t_command		**and_or;
  int			and_or_nbr;
}			t_tree;

/*
** free_tools.c
*/
void	free_tab(char**);
void	free_tree(t_tree**);
void    free_all(t_datas *, char **);
int	free_pid(int *);

/*
** tools.c
*/
int	my_strlen(char*);
void	my_strcpy(char*, char*);
int	my_strcmp_strict(char*, char*);
char	*free_line(char*, char*);
int	my_strcmp(char*, char*);

/*
** error.c
*/
int	my_int_perror(char*, int);
char	*my_char_perror(char*);
int	command_not_found(char*);

/*
** execute_command.c
*/
int	execute_command(t_datas *, char*);

/*
** get_tree.c
*/
int	get_tree(t_tree***, char*);

/*
** epure_str.c
*/
char	*epure_str(char*);

/*
** get_and_or_tree.c
*/
t_tree	*get_and_or_tree(char*);

/*
** get_interpipe_tree.c
*/
t_command	*get_interpipe_tree(char*);

/*
** get_command_tree.c
*/
t_interpipe	*get_command_tree(char*);

/*
** get_and_or_tree_add.c
*/
void	apply_and_or(t_command*, char*, int);
char	*get_inter_tab(char*, int);

/*
** str_to_wordtab.c
*/
char	**str_to_wordtab(char*);

/*
** fill_leaf.c
*/
int	fill_leaf(t_tree**);

/*
** get_redirect_files.c
*/
int	get_redirect_files(t_interpipe*, char*);

/*
** prompt.c
*/
int	aff_prompt(char**);
char	**get_prompt();
void	free_prompt(char**);

/*
** env_copy.c
*/
void	free_env(char**);
char	**env_copy(char**);
char	*copy_varenv(char*);

/*
** check_and_add_path.c
*/
int	check_and_add_path(t_interpipe**, char**);

/*
** slash_test.c
*/
int	slash_test(char*);

/*
** get_varenc.c
*/
char	*get_varenv(char**, char*);

/*
** get_varpath.c
*/
char	**get_varpath(char*);

/*
** open_fd.c
*/
int	open_fd(t_interpipe**);

/*
** execute_interpipe.c
*/
int	execute_interpipe(t_command*, t_datas *);

/*
** do_instruction.c
*/
int	do_instruction(t_command*, int, t_datas *);

/*
** double_left_red.c
*/
int     double_left_red(t_interpipe*);

/*
** builtins.c
*/
int	exec_builtins(char**, char***, t_datas *);
int	is_builtin(t_interpipe*, int);

/*
** setenv.c
*/
int     setenv_builtin(char***, char**);

/*
** unsetenv.c
*/
int	unsetenv_builtin(char***, char**);

/*
** env.c
*/
int	env_builtin(char***, char**);

/*
** echo.c
*/
int	echo_builtin(char***, char**);

/*
** exit.c
*/
int	exit_builtin(char***, char**);

/*
** cd.c
*/
int	cd_builtin(char***, char**);

/*
** tools_bis.c
*/
int	my_tablen(char**);
int	my_getnbr(char*);
int	my_strcat(char *, char *);
char	*my_malloc(int);

/*
** history.c
*/
t_history	*load_history(t_datas *, char *, char *, t_history *);
int		save_in_file(t_datas *, char *);
t_history	*add_a_command(t_history *, char *);
int		get_file_descriptor(char *, char *, char *);
int		free_history(t_history *);

/*
** profiles.c
*/
int		profile(char **, t_datas *);

/*
** aff_history.c
*/
int		aff_history(t_history *);
int		ret_history(t_datas *, t_history *, char *);

/*
** check_if_directory.c
*/
int	check_if_directory(char*);
int	check_if_exist(char*);
int     check_exit(t_tree**);
int	check_varenv_name(char*);
int	check_permission(char*, char);

/*
** check_command.c
*/
int	check_command(char*);

/*
** verif_command.c
*/
int	change_count_value(char*, t_counter*);
int	check_pipe_and_args(char*, t_counter*);
int	check_redir_and_args(char*, t_counter*);

/*
** match.c
*/
int	match(char, char*);

/*
** check_var.c
*/
int	check_var(t_interpipe**, char**, int);

/*
** my_getstr.c
*/
char	*my_getstr(int);

/*
** check_status.c
*/
int	check_status(int pid, int *ret);

/*
** alias.c
*/
t_alias	*load_alias(char *, char **, t_alias *);

/*
** alias_tools.c
*/
int	alias_length(char *);
char	*copy_str(char *);
void	free_alias(t_alias *);
int	cut_alias(char *, int, int, char **);

/*
** source_command.c
*/
char	*replace_by_alias(char *, t_alias *);

/*
** get_dir.c
*/
char	*my_getdir(char*);

/*
** get_dir_permission.c
*/
int	check_dir_permission(char*, char);

/*
** main.c
*/
void	handler(int);

/*
** alias_tools_bis.c
*/
t_alias		*manage_ret(t_alias *, t_alias *, int);
void		init_var(int *, char **, char **);
int		free_errors(char *, char *);

#endif /* !MYSH_H_ */
