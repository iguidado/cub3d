#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"


//# include "manage_error.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>

/*
** Il faut séparé le fichier .h en plusieur fichier 1 pour le parsing
** du fichier 1 autre pour les erreur aka (escape_bin) 
*/

# define TILES " 102NESW"
# define WALLS "1"
# define INTERIOR "02NESW"
# define SPAWN "NESW"
# define EXTERIOR " "
# define ID_NB 8
# define FOV M_PI / 4.0f

# define KEY_W 122
# define KEY_A 113
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65363 
# define KEY_RIGHT 65361
# define KEY_ESC 65307

enum
{
	FLAG_RES = 1,
	FLAG_CEIL = 2,
	FLAG_FLOOR = 4,
	FLAG_NO = 8,
	FLAG_SO = 16,
	FLAG_WE = 32,
	FLAG_EA = 64,
	FLAG_SPRI = 128
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
	char			**map;
}				t_config;

typedef struct	s_img
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
}				t_img;

typedef	struct	s_player
{
	float	x;
	float	y;
	float	angle;
	float	fov;
}				t_player;

typedef	struct	s_ray_x
{
	int		x;
	float	angle;
	float	eye_x;
	float	eye_y;
	float	len;
	int		test_x;
	int		test_y;
}				t_ray_x;

typedef struct	s_prm_pkg
{
	t_config	*cfg;
	t_img		*img;
	t_player	*one;
}				t_prm_pkg;

/*
**	Structure for games
*/

/*
**typedef struct	s_game2d
**{
**	struct s_config		cfg;
**	struct s_map		map;
**}				t_game2d;
*/

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
**	Get map
*/

void		ft_add_map(t_config *cfg, t_file_data *fdata);
int			ft_get_file(int fd, char **line);

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
**	Set Structure
*/

t_config	ft_preset_config(void);
t_file_data	ft_preset_fdata(int ac, char **av);
t_player	ft_preset_player(t_config *cfg);
t_img		ft_preset_img(t_config *cfg);
t_prm_pkg	ft_pkg_param(t_config *cfg, t_img *img, t_player *one);

/*
**	Str analysis : parse_utils
*/

int			ft_line_is_empty(char *line);
int			ft_line_is_map(char *line);
int			ft_count_param(char **param);
int			ft_str_isdigit(char *str);
int			ft_str_is_colorcode(char *str);

/*
** Utils
*/

int			ft_strequ(char *str1, char *str2);

/*
**	clean data struct
*/

void		ft_wipe_cfg(t_config *cfg);
void		ft_wipe_file_data(t_file_data *data);

/*
**	Manage error
*/

void		ft_print_error_file(int errnum, t_config *cfg, t_file_data *fdata);
void		ft_print_error_id(int errnum, t_config *cfg, t_file_data *fdata);
void		ft_print_error_token(int errnum, t_config *cfg, t_file_data *fdata);
void		ft_print_error_map(int	errnum, t_config *cfg, t_file_data *fdata);
void		ft_manage_parse_error(int errnum, t_config *cfg, t_file_data *data);

/*
**	test function
*/

void		ft_print_cfg(t_config *cfg);
void		ft_print_fdata(t_file_data *fdata);

#endif
