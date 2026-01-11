/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:29:53 by ikarouat          #+#    #+#             */
/*   Updated: 2024/12/04 23:35:28 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(s + s_len));
	i = 0;
	while (i < s_len)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*heap_arr;
	size_t	len;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	len = count * size;
	heap_arr = malloc(count * size);
	if (!heap_arr)
		return (NULL);
	while (len > 0)
		*(unsigned char *)(heap_arr + (--len)) = 0;
	return (heap_arr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*new_s;
	size_t	s_len;

	if (!s1)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s1);
	new_s = (char *)malloc(s_len + 1);
	if (!new_s)
		return (NULL);
	while (i < s_len)
	{
		new_s[i] = s1[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
