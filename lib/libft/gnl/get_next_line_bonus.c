/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:17:37 by ikarouat          #+#    #+#             */
/*   Updated: 2024/12/13 15:48:03 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_join_and_free(char *dst, char *src)
{
	char	*new_buff;
	int		i;
	int		len;
	char	*tmp;

	if (!dst)
		return (ft_strdup(src));
	if (!src)
		return (ft_strdup(dst));
	len = ft_strlen(dst) + ft_strlen(src);
	new_buff = malloc(len + 1);
	if (!new_buff)
		return (NULL);
	i = 0;
	tmp = (char *) dst;
	while (*(tmp) != '\0')
		new_buff[i++] = *(tmp++);
	tmp = (char *) src;
	while (*(tmp) != '\0')
		new_buff[i++] = *(tmp++);
	new_buff[i] = '\0';
	free(dst);
	return (new_buff);
}

int	ft_read_line(int fd, char **buffer_p)
{
	char	*buffer;
	ssize_t	bytes_count;

	bytes_count = 0;
	while (!ft_strchr(*buffer_p, '\n'))
	{
		buffer = ft_calloc((size_t)(BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (-1);
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		if (bytes_count < 0)
		{
			free(buffer);
			return (-1);
		}
		if (bytes_count == 0)
		{
			free(buffer);
			return (0);
		}
		*buffer_p = ft_join_and_free(*buffer_p, buffer);
		free(buffer);
	}
	return (bytes_count);
}

char	*ft_get_remainder(char *s, size_t new_line_offset)
{
	size_t	i;
	char	*new_buf;

	i = 0;
	new_buf = ft_calloc(ft_strlen(s) - new_line_offset + 1, 1);
	if (!new_buf)
		return (NULL);
	while (s[new_line_offset + i])
	{
		new_buf[i] = s[new_line_offset + i];
		i++;
	}
	return (new_buf);
}

char	*ft_get_line(char **buffer_p)
{
	size_t	i;
	short	has_rem;
	char	*line;
	char	*s_remainder;

	i = 0;
	has_rem = 0;
	s_remainder = 0;
	while ((*buffer_p)[i] != '\n' && (*buffer_p)[i])
		i++;
	if ((*buffer_p)[i] == '\n')
		has_rem = 1;
	i++;
	line = (char *)ft_calloc(i + 1, 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *buffer_p, i + 1);
	if (has_rem)
		s_remainder = ft_get_remainder(*buffer_p, i);
	free(*buffer_p);
	*buffer_p = s_remainder;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	ssize_t		read_status;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1023)
		return (NULL);
	read_status = ft_read_line(fd, &buffer[fd]);
	if (read_status == -1 || !buffer[fd])
		return (NULL);
	line = ft_get_line(&buffer[fd]);
	return (line);
}
