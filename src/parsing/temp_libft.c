#include "parsing.h"

/* ========== ft_strlen ========== */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/* ========== ft_strdup ========== */
char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (*s)
		*dup++ = *s++;
	*dup = '\0';
	return (dup - len);
}

/* ========== ft_isdigit ========== */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/* ========== ft_atoi ========== */
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\f' || *str == '\v'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/* ========== ft_strncmp ========== */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

/* ========== ft_substr ========== */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/* ========== ft_split ========== */
static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, int *pos)
{
	int		start;
	int		len;
	char	*word;

	while (s[*pos] == c)
		(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != c)
		(*pos)++;
	len = *pos - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_substr(s, start, len);
	while (len--)
		word[len] = s[start + len];
	word[*pos - start] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		i;
	int		pos;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split = malloc((words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < words)
	{
		split[i] = get_word(s, c, &pos);
		if (!split[i])
		{
			free_array(&split);
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}

/* ========== ft_putstr_fd ========== */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

/* ========== get_next_line ========== */
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static char	*ft_strchr_gnl(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i - len1 < len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	free(s1);
	return (result);
}

static char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*save_remainder(char *buffer)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remainder = malloc(ft_strlen(buffer) - i);
	if (!remainder)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		chunk[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer && ft_strchr_gnl(buffer, '\n'))
		{
			line = extract_line(buffer);
			buffer = save_remainder(buffer);
			return (line);
		}
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
			{
				free(buffer);
				buffer = NULL;
				return (NULL);
			}
			line = buffer;
			buffer = NULL;
			return (line);
		}
		chunk[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, chunk);
		if (!buffer)
			return (NULL);
	}
	return (NULL);
}

