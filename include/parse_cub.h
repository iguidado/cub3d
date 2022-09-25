#ifndef PARSE_CUB_H
# define PARSE_CUB_H

# include <stdbool.h>
# define TILES " 102NESW"
# define WALLS "1"
# define INTERIOR "02NESW"
# define SPAWN "NESW"
# define EXTERIOR " "

# define ID_NB 8
enum
{
	FLAG_CEIL = 1,
	FLAG_FLOOR = 2,
	FLAG_NO = 4,
	FLAG_SO = 8,
	FLAG_WE = 16,
	FLAG_EA = 32
};

typedef	struct	s_dot
{
	int x;
	int y;
}				t_dot;

typedef struct	s_spawn
{
	struct s_dot	pos;
	float			angle;
}				t_spawn;

typedef struct	s_obj_spwn
{
	t_dot			pos;
	struct s_obj_spwn	*next;
}		t_obj_spwn;

/*
** Temporary structure for processing .cub file
**	Don't try to free(name) as it is an argument so it's on the stack
*/

typedef	struct	s_file_data
{
	char	*name;
	int		fd;
	int		line_nb;
	char	*line;
	char	**paramlist;
}				t_file_data;

/*
** all information in file.cub are stocked in s_config structure
** 
*/

typedef struct	s_map
{
	char	**data;
	t_dot	res;
}				t_map;

typedef struct	s_config
{
	unsigned char	mask;
	int				screen_width;
	int				screen_height;
	int				ceilar_color;
	int				floor_color;
	char			*no_text;
	char			*so_text;
	char			*ea_text;
	char			*we_text;
	char			*spri_text;
	t_spawn			spwn;
	t_map			map;
	t_obj_spwn		*obj_list;
}				t_config;

/*
** errnum for exit/error call
*/

enum
{
	ERROR_SYSCALL, 
	ERROR_FILE_END, ERROR_MISS_CONF,
	ERROR_DUPLICATE, ERROR_ID,
	ERROR_LEXICAL, ERROR_SYNTAX, 
	ERROR_MAP_PLAYER_SPAWN, ERROR_MAP_EMPTY_LINE, 
	ERROR_MAP_OPEN_BOUNDARIES, ERROR_MAP_BAD_TILE,
	NB_OF_ERROR_FROM_CFG
};

/*
** Parsing function
*/

t_config	ft_parse_cub(int ac, char **av);
t_config	ft_get_config(t_file_data *fdata);
int			ft_get_fd(int ac, char **av);
int			ft_get_next_param(t_file_data *fdata);
int			ft_fdata_to_cfg(t_config *cfg, t_file_data *fdata);

/*
** Get texture
*/

int			ft_get_no_text(t_config *cfg, t_file_data *fdata);
int			ft_get_so_text(t_config *cfg, t_file_data *fdata);
int			ft_get_ea_text(t_config *cfg, t_file_data *fdata);
int			ft_get_we_text(t_config *cfg, t_file_data *fdata);
int			ft_get_spri_text(t_config *cfg, t_file_data *fdata);

/*
**	Get num value
*/

int			ft_get_res(t_config *cfg, t_file_data *fdata);
int			ft_get_ceilar(t_config *cfg, t_file_data *fdata);
int			ft_get_floor(t_config *cfg, t_file_data *fdata);

/*
**	Str analysis : parse_utils
*/

int			ft_line_is_empty(char *line);
int			ft_line_is_map(char *line);
int			ft_count_param(char **param);
int			ft_str_isdigit(char *str);
int			ft_str_is_colorcode(char *str);

/*
**	Map analysis utils : don't know if i should check
**	for corner or keep my oob_checker (wich is pretty heavy)
*/

char		ft_istile(char c);
int			ft_is_border_map(char **map, int x, int y);
int			ft_check_surrounding_rows(t_config *cfg, int x, int y);
void		ft_check_tile_type(t_config *cfg, t_file_data *fdata, int x, int y);

/*
**	Get map and map data
*/

void		ft_add_map(t_config *cfg, t_file_data *fdata);
int			ft_add_row(char ***ptr_map, char *row);
void		ft_process_map(t_config *cfg, t_file_data *fdata);
void		ft_get_spawn(t_config *cfg, t_file_data *fdata, int x, int y);

/*
** Add map utils
*/

void	ft_process_tile(t_config *cfg, t_file_data *fdata, int x, int y);
int		ft_add_row(char ***ptr_map, char *row);
void	ft_get_spawn(t_config *cfg, t_file_data *fdata, int x, int y);

#endif
