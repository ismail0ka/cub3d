/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:42:12 by ikarouat          #+#    #+#             */
/*   Updated: 2026/01/15 04:42:12 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

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

/* ************************************************************************** */
/*                               DEFINES                                      */
/* ************************************************************************** */

# define ALL_TEXTURES 4
# define NORTH_TEX 0
# define SOUTH_TEX 1
# define WEST_TEX 2
# define EAST_TEX 3

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_lines
{
	char			*line;
	struct s_lines	*next;
}	t_lines;

typedef struct s_playerdata
{
	int		pixel_x;
	int		pixel_y;
	int		cell_x;
	int		cell_y;
	char	direction;
}	t_playerdata;

typedef struct s_raydata
{
	double	distance_per_x;
	double	distance_per_y;
	double	dir_x;
	double	dir_y;
	double	ray_length;
}	t_raydata;

typedef struct s_params
{
	char			**map;
	char			*textures[ALL_TEXTURES];
	int				floor_color[3];
	int				ceiling_color[3];
	t_playerdata	*player;
	t_raydata		*ray;
	int				player_move;
}	t_params;

/* ************************************************************************** */
/*                         FUNCTION PROTOTYPES                                */
/* ************************************************************************** */

/* check_map.c */
int			check_map_elements(t_params *params);
int			is_map_surrounded(void);

/* map_cleanup.c */
int			replace_spaces_with_walls(void);

/* helper_utils.c */
void		free_array(char ***arr);

/* line_utils.c */
t_lines		*new_line(char *str);
void		add_line(t_lines **head, t_lines *line);
t_lines		*last_line(t_lines *head);
size_t		lines_count(t_lines *head);
void		free_lines(t_lines **head);

/* param_utils.c */
t_params	*params_holder(void);
void		separate_init(t_params **params, t_raydata *ray,
				t_playerdata *player);
void		params_init(t_params **params, t_raydata *ray,
				t_playerdata *player);
void		free_params(t_params **params);

/* parce_args.c */
int			parse_args(char *filename);

/* read_file.c */
int			parse_content(t_lines *file_content);
t_lines		*extract_file_content(int fd);

/* separate_elements_colors.c */
int			add_color(t_lines *file_content);

/* separate_elements_map.c */
int			add_map(t_lines *file_content_i);

/* separate_elements_textures.c */
int			add_tex(t_lines *file_content);

/* sparate_elements.c */
int			separate_elements(t_lines *file_content);

#endif
