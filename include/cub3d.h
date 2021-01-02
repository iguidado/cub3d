/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 11:38:30 by iguidado          #+#    #+#             */
/*   Updated: 2021/01/02 13:59:07 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parse_cub.h"

/*
** Authorized library
*/

# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

/*
** Il faut séparé le fichier .h en plusieur fichier 1 pour le parsing
** du fichier 1 autre pour les erreur aka (escape_bin)
*/

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65363
# define KEY_RIGHT 65361
# define KEY_ESC 65307

# define FOV (M_PI / 4.0f)
# define PLAYER_SPEED 0.1f

# define KEY_PRESS 1
# define KEY_RELEASE 2
# define EVENT_EXIT 17
/*
**	Structure for games
*/

typedef enum e_input
{
	INPUT_W,
	INPUT_A,
	INPUT_S,
	INPUT_D,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_ESC,
	NB_INPUT
}			t_input;

typedef struct	s_fdot
{
	float x;
	float y;
}				t_fdot;

typedef struct	s_pos_lst
{
	t_fdot				pos;
	struct s_pos_lst	*next;
}				t_pos_lst;

typedef struct	s_text
{
	void	*ptr;
	char	*data;
	int		width;
	int		height;
}				t_text;

typedef struct	s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		img_width;
	int		img_height;
	t_text	no_text;
	t_text	so_text;
	t_text	ea_text;
	t_text	we_text;
	t_text	spri_text;
}				t_img;

typedef struct	s_bmp_header
{
	unsigned short	type;
	unsigned int	file_size;
	unsigned short	res1;
	unsigned short	res2;
	unsigned int	offset;
	unsigned int	dib_header_size;
	int				width_px;
	int				height_px;
	unsigned short	num_planes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	image_size_bytes;
	int				x_resolution_ppm;
	int				y_resolution_ppm;
	unsigned int	num_colors;
	unsigned int	important_colors;
}				t_bmp_header;

typedef struct	s_bmp_image
{
	t_bmp_header	header;
	unsigned char	*data;
}				t_bmp_image;

typedef	struct	s_player
{
	float	x;
	float	y;
	float	angle;
	float	fov;
	float	speed;
	int		key_id[NB_INPUT];
	bool	input[NB_INPUT];
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

/*
**	No need to clean block since wall_text is part of t_img
*/

typedef struct	s_block
{
	t_dot	pos;
	t_fdot	midpoint;
	t_fdot	hitpoint;
	float	test_angle;
	float	sample_x;
	t_text	*wall_text;
}				t_block;

typedef struct	s_obj
{
	float	angle;
	float	ceiling;
	float	floor;
	float	a_ratio;
	float	width;
	float	height;
	float	middle;
	float	dist;
}				t_obj;

typedef struct	s_spri_coord
{
	float ly;
	float lx;
	float sample_y;
	float sample_x;
	int screen_x;
}				t_spri_coord;

typedef struct	s_prm_pkg
{
	t_config	*cfg;
	t_img		*img;
	t_player	*one;
	t_pos_lst	*obj_lst;
	float		*z_buffer;
}				t_prm_pkg;

/*
**	Set Structure
*/

t_file_data	ft_preset_fdata(int ac, char **av);
t_config	ft_preset_config(void);
t_prm_pkg	ft_pkg_prm(t_config *cfg, t_img *img, t_player *one, t_pos_lst **obj);

/*
**	Load game
*/
t_img		ft_preset_img(t_config *cfg);
t_text		ft_load_text(t_img *img, char *text_name);
t_player	ft_preset_player(t_config *cfg);
t_pos_lst	*ft_load_obj(t_obj_spwn *obj_list);

/*
**	ft_inputs : function hooked by input
**	also input conditioned function in main loop
*/


int			ft_get_input(int keycode, void *param);
int			ft_release_input(int keycode, void *param);
void		ft_move_player(t_player *one);
void		ft_escape_game(t_prm_pkg *cub);
int			ft_prep_escape(t_prm_pkg *pkg);

/*
**	ft_render_screen :
**	Render the game aka img.data
**	manipulation and raycasting
*/
int			ft_render_screen(void *param);
void		ft_raycasting(t_prm_pkg *cub);
int			ft_raycast(t_prm_pkg *cub, t_ray_x *ray);
void		ft_fill_height_void(t_config *cfg, t_img *img, t_ray_x *ray);
void		ft_fill_height(t_prm_pkg *cub, t_ray_x *ray, t_block *block);

/*
**	ft_get_key : Manage hooked key
*/
int			ft_get_key(int keycode, void *param);

/*
** Utils
*/

int			ft_is_oob(t_map *map, float x, float y);
int			ft_strequ(char *str1, char *str2);
void		ft_escape_game(t_prm_pkg *cub);

/*
**	clean data struct
*/

void		ft_wipe_cfg(t_config *cfg);
void		ft_wipe_file_data(t_file_data *data);
void		ft_wipe_obj_spwn(t_obj_spwn **obj_lst);
void		ft_wipe_obj(t_pos_lst **obj_lst);
void		ft_wipe_img(t_img *img);

/*
**	Manage error
*/

void		ft_manage_parse_error(int errnu, t_config *cfg, t_file_data *fdata);
void		ft_print_error_file(int errnum, t_config *cfg, t_file_data *fdata);
void		ft_print_error_id(int errnum, t_config *cfg, t_file_data *fdata);
void		ft_print_error_token(int errnum, t_config *cfg, t_file_data *fdata);
void		ft_print_error_map(int errnum, t_config *cfg, t_file_data *fdata);

/*
**	ft_manage_block
*/

t_block		ft_get_block(t_config *cfg, t_ray_x *ray, t_player *one);
void		ft_add_wall_to_block(t_img *img, t_block *block);
int			ft_get_wall_pixel(float sample_y, t_block *block);
float		ft_get_sample_y(int i, int scrn_width, int ceiling, int floor);

/*
**	ft_manage_obj
*/

int			ft_is_inscrn(t_config *cfg, t_player *one, t_fdot pos, t_obj *obj);
void		ft_complete_obj(t_config *cfg, t_img *img, t_obj *obj);
void		ft_spri_pix(t_img *img, int *screen, t_spri_coord *spri, int ceil);
void		ft_paint_spri_x(int	spri_x, t_prm_pkg *pkg, t_obj *obj);
void		ft_manage_obj(t_prm_pkg *pkg);

/*
**	ft_print_data
*/

void		ft_print_fdata(t_file_data *fdata);
void		ft_print_cfg(t_config *cfg);
void		ft_print_obj(t_obj_spwn *obj_list);

/*
** ft_export_bmp
*/

void		ft_export_bmp(t_img *img);
void		ft_write_pixmap(t_img *img, int fd);
void		ft_init_bmp_hdr(t_img *img, t_bmp_header *hdr);
void		ft_write_bmp_hdr(int fd, t_bmp_header *hdr);

#endif
