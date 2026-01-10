#include "parsing.h"

/**
 * replace_spaces_with_walls - Replaces internal spaces in the map with walls
 * After the map has been validated as surrounded, any remaining spaces
 * (which were inside the playable area) are replaced with walls ('1')
 * 
 * This function modifies the map in-place, replacing all space characters
 * with '1' (walls), effectively closing up any gaps that were in the design.
 * 
 * @return: 0 on success, -1 on failure
 */
int	replace_spaces_with_walls(void)
{
	t_params	*param;
	int			i;
	int			j;

	param = params_holder();
	if (!param || !param->map)
		return (-1);
	
	i = 0;
	while (param->map[i])
	{
		j = 0;
		while (param->map[i][j])
		{
			if (param->map[i][j] == ' ')
				param->map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (0);
}
