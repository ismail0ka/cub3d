#include "parsing.h"

void	free_array(char ***arr)
{
	int	index;

	index = -1;
	if (!arr)
		return ;
	if (!(*arr))
		return ;
	while ((*arr)[++index])
		free((*arr)[index]);
	free(*arr);
	(*arr) = NULL;
}