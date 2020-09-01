/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preset_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:48:50 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 00:21:14 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	t_file_data	ft_init_fdata(int ac, char **av)
**	{
**		t_file_data fdata;
**
**		if (ac < 2 || ac > 4)
**		{
**			ft_putendl("Error\nBad nbr of argument");
**			exit(EXIT_FAILURE);
**		}
**		if ((fdata.fd = open(av[1], O_RDONLY)) < 0)
**		{
**			perror(av[1]);
**			exit(errno);
**		}
**		fdata.name = av[1];
**		fdata.line_nb = 0;
**		fdata.line = NULL;
**		fdata.paramlist = NULL;
**		return (fdata);
**	}
*/

int			ft_init_fdata(int ac, char **av, t_file_data *new)
{
	new->line_nb = 0;
	new->name = av[1];
	new->line = NULL;
	new->paramlist = NULL;
	if (ac < 2 || ac > 3)
		return (ERROR_NB_ARGS);
	if (ac == 3 && !ft_strequ(av[2], "--save"))
		return (ERROR_INVALID_ARG);
	if (!ft_endwith(av[1], ".cub"))
		return (ERROR_INVALID_FILE);
	if ((new->fd = open(av[1], O_RDONLY)) == -1)
		return (ERROR_SYSCALL);
	return (-1);
}

t_config	ft_init_config(void)
{
	t_config new;

	new.mask = 0;
	new.screen_width = -1;
	new.screen_height = -1;
	new.ceilar_color = -1;
	new.floor_color = -1;
	new.no_text = NULL;
	new.so_text = NULL;
	new.ea_text = NULL;
	new.we_text = NULL;
	new.spri_text = NULL;
	new.spwn.pos.x = -1;
	new.spwn.pos.y = -1;
	new.spwn.angle = -1;
	new.map.data = NULL;
	new.map.res.x = 0;
	new.map.res.y = 0;
	new.obj_list = NULL;
	return (new);
}

t_player	ft_preset_player(t_config *cfg)
{
	t_player new;

	new.x = ((float)cfg->spwn.pos.x) + 0.5f;
	new.y = ((float)cfg->spwn.pos.y) + 0.5f;
	new.angle = cfg->spwn.angle;
	new.fov = FOV;
	new.speed = PLAYER_SPEED;
	new.key_id[INPUT_W] = KEY_W;
	new.key_id[INPUT_A] = KEY_A;
	new.key_id[INPUT_S] = KEY_S;
	new.key_id[INPUT_D] = KEY_D;
	new.key_id[INPUT_LEFT] = KEY_LEFT;
	new.key_id[INPUT_RIGHT] = KEY_RIGHT;
	new.key_id[INPUT_ESC] = KEY_ESC;
	ft_memset(new.input, 0, sizeof(new.input));
	return (new);
}

int			ft_preset_img(t_config *cfg, t_img *new)
{
	t_dot	res_max;
	int		bpp;
	int		linelen;
	int		endian;

	ft_memset(new, 0, sizeof(*new));
	if (!(new->mlx_ptr = mlx_init()))
		return (ERROR_MLX_INIT);
	mlx_get_screen_size(new->mlx_ptr, &res_max.y, &res_max.x);
	if (res_max.y < cfg->screen_width)
		cfg->screen_width = res_max.y;
	if (res_max.x < cfg->screen_height)
		cfg->screen_height = res_max.x;
	if (!(new->win_ptr = mlx_new_window(new->mlx_ptr, cfg->screen_width
			, cfg->screen_height, "cub3d")))
		return (ERROR_MLX_NEW_WIN);
	if (!(new->img_ptr = mlx_new_image(new->mlx_ptr, cfg->screen_width
			, cfg->screen_height)))
		return (ERROR_MLX_SCREEN);
	new->img_data = mlx_get_data_addr(new->img_ptr, &bpp, &linelen, &endian);
	new->img_width = cfg->screen_width;
	new->img_height = cfg->screen_height;
	if (!ft_load_all_text(new, cfg))
		return (ERROR_MLX_NEW_IMG);
	return (0);
}

int			ft_init_pkg(t_config *cfg, t_prm_pkg *pkg)
{
	int	errnum;

	ft_memset(pkg, 0, sizeof(*pkg));
	pkg->cfg = cfg;
	if (!(pkg->one = malloc(sizeof(*pkg->one))))
		return (ERROR_SYSCALL);
	*pkg->one = ft_preset_player(cfg);
	if (!(pkg->img = malloc(sizeof(*pkg->img))))
		return (ERROR_SYSCALL);
	if ((errnum = ft_preset_img(cfg, pkg->img)))
		return (errnum);
	if (!(pkg->obj_lst = ft_load_obj(cfg->obj_list)))
		return (ERROR_SYSCALL);
	if (!(pkg->z_buffer = malloc(sizeof(float) * pkg->img->img_width + 1)))
		return (ERROR_SYSCALL);
	return (0);
}
