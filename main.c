#include "pipex.h"

char	*find_path(t_data *d, char *str, char **env, int i)
{
	char	**global_path;

	while (*env)
	{
		if (strnstr(*env, "PATH=", 5))
			global_path = ft_split(&env[0][5], ':');
		env++;
	}
	while (global_path && global_path[i])
	{
		d->tmp = ft_strjoin(global_path[i], "/");
		d->curr_path = ft_strjoin(d->tmp, str);
		if (access(d->curr_path, X_OK) != -1)
		{
			free_strs(global_path, NULL);
			return (d->curr_path);
		}
		i++;
	}
	free_strs(global_path, NULL);
	return (NULL);
}

void	run_cmd1(t_data *d, char **av, char **env)
{
	d->cmd1 = ft_split(av[2], ' ');
	d->path1 = find_path(d, d->cmd1[0], env, 0);
	if (d->path1 == NULL)
		ft_quit(d->cmd1[0]);
	dup2(d->pipefd[1], STDOUT_FILENO);
	dup2(d->file1, STDIN_FILENO);
	close_fd(d);
	d->curr_path = NULL;
	d->tmp = NULL;
	execve(d->path1, d->cmd1, env);
}

void	run_cmd2(t_data *d, char **av, char **env)
{
	d->cmd2 = ft_split(av[3], ' ');
	d->path2 = find_path(d, d->cmd2[0], env, 0);
	if (d->path2 == NULL)
		ft_quit(d->cmd2[0]);
	dup2(d->pipefd[0], STDIN_FILENO);
	dup2(d->file2, STDOUT_FILENO);
	close_fd(d);
	execve(d->path2, d->cmd2, env);
}

void	ft_quit(char *str)
{
	if (errno)
		perror(str);
	else
		ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{	
	t_data	data;

	if (ac != 5)
		ft_quit("model : ./pipex file1 cmd1 cmd2 file2\n");
	data.file1 = open(av[1], O_RDONLY);
	if (data.file1 == -1)
		ft_quit(av[1]);
	data.file2 = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (data.file2 == -1)
		ft_quit(av[4]);
	if (pipe(data.pipefd) == -1)
		ft_quit("Error : pipe file descriptors initialization failed\n");
	data.pid1 = fork();
	if (data.pid1 == 0)
		run_cmd1(&data, av, env);
	data.pid2 = fork();
	if (data.pid2 == 0)
		run_cmd2(&data, av, env);
	close_fd(&data);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	free(data.curr_path);
	free(data.tmp);
	return (0);
}
