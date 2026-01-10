#ifndef TEMP_LIBFT_H
# define TEMP_LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* External function dependencies (libft & get_next_line) */
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
char		*get_next_line(int fd);

#endif
