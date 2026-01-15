/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoessedr <yoessedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:13 by yoessedr          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:13 by yoessedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**copy_and_replace(void);

static int	find_last_non_space(char *str)
{
	int	i;
	int	last_char;

	last_char = -1;
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ')
			last_char = i;
		i++;
	}
	return (last_char);
}

static void	fill_padded_string(char *ret, char *str, int longest, int last_char)
{
	int	index;
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	index = -1;
	while (++index < longest)
	{
		if (index < i)
			ret[index] = str[index];
		else if (index <= last_char)
			ret[index] = '1';
		else
			ret[index] = '?';
	}
	ret[index] = '\0';
}

static char	*replace_space(char *str, int longest)
{
	char	*ret;
	int		last_char;

	ret = malloc(sizeof(char) * longest + 1);
	if (!ret)
		return (NULL);
	last_char = find_last_non_space(str);
	fill_padded_string(ret, str, longest, last_char);
	return (ret);
}

static char	**copy_and_replace(void)
{
	t_params	*param;
	int			index;
	int			longest;
	char		**ret;
	int			len;

	index = -1;
	longest = 0;
	param = params_holder();
	while (param->map[++index])
	{
		len = ft_strlen(param->map[index]);
		if (param->map[index][len - 1] == '\n')
			len--;
		if (longest < len)
			longest = len;
	}
	ret = malloc((index + 1) * sizeof(char *));
	if (!ret)
		return (perror("cub3D"), NULL);
	index = -1;
	while (param->map[++index])
		ret[index] = replace_space(param->map[index], longest);
	ret[index] = NULL;
	return (ret);
}

int	is_map_surrounded(void)
{
	char		**map;
	t_params	*param;
	int			result;

	param = params_holder();
	map = copy_and_replace();
	if (!map)
		return (-1);
	result = check_is_map_open(map);
	free_array(&map);
	if (result == -1)
		return (-1);
	return (0);
}
