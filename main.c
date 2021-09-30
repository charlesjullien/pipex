/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjullien <marvin@42.fr>                    +#+  +:+       +#+        *///changer pour student
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:13:50 by cjullien          #+#    #+#             */
/*   Updated: 2021/09/30 18:57:40 by cjullien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *str, char **env, int i)
{
	char	**global_path;

	while (*env)
	{
		if (strnstr(*env, "PATH=", 5))
			global_path = ft_split(&env[0][5], ':');
		*env++;
	}
	while (global_path && global_path[i])
	{
		d->tmp = ft_strjoin(global_path[i], "/");
		d->curr_path = ft_strjoin(d->tmp, str);
		if (access(d->curr_path, X_OK) != -1)//?
		{
			free_strs(global_path, NULL);
			return (d->curr_path);
		}
	}
	free_strs(global_path, NULL);
	return (NULL);
}

void	run_cmd1(t_data *d, char **av, char **env)//free tmp et curr_path dans run cmd2
{
	d->cmd1 = ft_split(av[2], ' ');
	d->path1 = find_path(d->cmd1, env, 0);
	if (d->path1 == NULL)
		ft_quit(d->cmd1;//add [0] ?
	dup2(d->pipefd[1], STDOUT_FILENO);
	dup2(d->file1, STDIN_FILENO);
	close_fd(d);
	execve(d->path1, d->cmd1, env);
	d->curr_path = NULL;
	d->tmp = NULL;
}

void	run_cmd2(t_data *d, char **av, char **env)//free tmp et curr_path dans run cmd2
{
	d->cmd2 = ft_split(av[3], ' ');
	d->path2 = find_path(d->cmd2, env, 0);
	if (d->path2 == NULL)
		ft_quit(d->cmd2);//add [0]?
	dup2(d->pipefd[0], STDIN_FILENO);
	dup2(d->file2, STDOUT_FILENO);
	close_fd(d);
	execve(d->path2, d->cmd2, env);
	free(d->curr_path);
	free(d->tmp);
}

int	ft_quit(char *str)
{
	ft_putstr_fd(str, 0);
	return (0);
}

int main(int ac, char **av, char **env)
{	
	t_data data;

	if (ac != 5)
		return (ft_quit("Error : Wrong number fo arguments. Usage = ./pipex file1 cmd1 cmd2 file2\n"));
	data.file1 = open(av[1], O_RDONLY);
	if (data.file1 == -1)
		return (ft_quit("Error : read error on file1\n"));
	data.file2 = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (data.file2 == -1)
		return (ft_quit("Error : read error on file2\n"));
	if (pipe(data.pipefd) == -1)
		return (ft_quit("Error : pipe file descriptors initialization failed\n"));
	data.pid1 = fork();	
	if (data.pid1 == 0)
		run_cmd1(&data, av, env);
	return (0);
}
