/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjullien <cjullien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:22:34 by cjullien          #+#    #+#             */
/*   Updated: 2021/10/06 13:04:13 by cjullien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data	t_data;
struct			s_data
{
	int		file1;
	int		file2;
	int		pipefd[2];
	int		pid1;
	int		pid2;
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
};

char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	free_strs(char **big, char	*small);
void	close_fd(t_data *d);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_quit(char *str, int i);
int		check_no_space(char *str);
int		ft_strlen(char const *str);

#endif
