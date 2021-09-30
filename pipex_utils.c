#include "pipex.h"

void	free_strs(char **big, char	*small)
{
	int	i;

	i = 0;
	if (big)
	{
		while (big[i])
		{
			free(big[i]);
			i++;
		}
		free(big);
	}
	if (small)
		free(small);
}

void	close_fd(t_data *d)
{
	close(d->pipefd[0]);
	close(d->pipefd[1]);
	close(d->file1);
	close(d->file2);
}
