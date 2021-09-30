#ifndef PIPEX_H
# define PIPEX_H
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data	t_data;
struct			s_data
{
	int		file1;
	int		file2;
	int		pipefd[2];
	int		pid1;
	int		pid2;
	char	*cmd1;
	char	*cmd2;
	char	*path1;
	char	*path2;
	char	*tmp;
	char	*curr_path;
};

#endif
