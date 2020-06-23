/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:52:36 by iguidado          #+#    #+#             */
/*   Updated: 2020/06/23 00:05:32 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*wrap_mlx_get_addr_data(void *img_ptr)
{
	int		bpp;
	int		line_size;
	int		endian;
	char	*img_data;

	img_data = mlx_get_data_addr(img_ptr, &bpp, &line_size, &endian);
	return (img_data);
}

int		ft_is_oob(char **map, float x, float y)
{
	int i;
	int j;

	if (x < 0.0f || y < 0.0f)
		return (1);
	i = 0;
	j = 0;
	while (map[i] && i < (int)y)
		i++;
	if (!map[i])
		return (1);
	while (map[i][j] && j < (int)x)
		j++;
	if (!map[i][j])
		return (1);
	return (0);
}

void		ft_move_player(int keycode, t_player *one)
{
	if (keycode == KEY_W)
	{
		one->y += cos(one->angle) * 0.1f;
		one->x += sin(one->angle) * 0.1f;
	}
	else if (keycode == KEY_A)
	{
		one->x -= cos(one->angle) * 0.1f;
		one->y += sin(one->angle) * 0.1f;
	}
	else if (keycode == KEY_S)
	{
		one->y -= cos(one->angle) * 0.1f;
		one->x -= sin(one->angle) * 0.1f;
	}
	else if (keycode == KEY_D)
	{
		one->x += cos(one->angle) * 0.1f;
		one->y -= sin(one->angle) * 0.1f;
	}
}

t_player	ft_cpy_player(t_player *one)
{
	t_player two;

	two.angle = one->angle;
	two.x = one->x;
	two.y = one->y;
	two.fov = one->fov;
	return (two);
}

int		ft_escape_game(t_prm_pkg *cub)
{
	printf("escaping game\n");
//	free(cub->z_buffer);
/*
**	ft_wipe_img(cub->img);
**	ft_wipe_cfg(cub->cfg);
**	ft_wipe_obj(&cub->obj_lst);
*/
	exit(0);
	return (0);
}

int		ft_get_key(int keycode, void *param)
{
	t_prm_pkg	*cub;
	t_player	one_ghost;

	cub = (t_prm_pkg *)param;
	one_ghost = *cub->one;
	if (keycode == KEY_LEFT)
	{
		one_ghost.angle += 0.1f;
	}
	else if (keycode == KEY_RIGHT)
	{
		one_ghost.angle -= 0.1f;
	}
	else if (keycode == KEY_ESC)
		ft_escape_game(cub);
	ft_move_player(keycode, &one_ghost);
	if (!ft_is_oob(cub->cfg->map, one_ghost.x, one_ghost.y))
		*cub->one = ft_cpy_player(&one_ghost);
	ft_render_screen(param);
	return (0);
}

void		ft_write_pixmap(t_img *img, int fd)
{
	int i;

	img->img_height--;
	while (img->img_height >= 0)
	{
		i = 0;
		while (i < img->img_width)
		{
		//	write(fd, &(img->img_data[(img->img_height * img->img_width * 4) + (i * 4) + 3]), 1);
		//	write(fd, &(img->img_data[(img->img_height * img->img_width * 4) + (i * 4) + 2]), 1);
		//	write(fd, &(img->img_data[(img->img_height * img->img_width * 4) + (i * 4) + 1]), 1);
		//	write(fd, &(img->img_data[(img->img_height * img->img_width * 4) + (i * 4)]), 1);
			write(fd, &(img->img_data[(img->img_height * img->img_width * 4) + (i * 4)]), 4);
	//		printf("%x, ", ((int *)img->img_data)[(img->img_height * img->img_width) + (i)]);
			i++;
		}
		img->img_height--;
	}
}

void		ft_export_bmp(t_img *img)
{
	int				fd;
	t_bmp_header	hdr;
	unsigned char	*data;

	fd = open("firstimage.bmp", O_CREAT|O_TRUNC|O_RDWR, S_IRWXU);
	hdr.type = 0x4d42;
	hdr.offset = 54;
	hdr.image_size_bytes = (img->img_width * img->img_height * 4);
	hdr.file_size = hdr.offset + hdr.image_size_bytes;
	hdr.dib_header_size = 40;
//	printf("|%lu|\n", sizeof(hdr));
	hdr.res1 = 0;
	hdr.res2 = 0;
	hdr.width_px = img->img_width;
	hdr.height_px = img->img_height;
	hdr.bpp = 16;
	hdr.compression = 0;
	hdr.num_planes = 1;
	hdr.num_colors = 0;
	hdr.important_colors = 0;
	hdr.x_resolution_ppm = 0;
	hdr.y_resolution_ppm = 0;
	hdr.num_colors = 0;
	hdr.important_colors = 0;
	write(fd, ((char *)&hdr.type), sizeof(hdr.type));
	write(fd, ((char *)&hdr.file_size), sizeof(hdr.file_size));
	write(fd, ((char *)&hdr.res1), sizeof(hdr.res1));
	write(fd, ((char *)&hdr.res2), sizeof(hdr.res2));
	write(fd, ((char *)&hdr.offset), sizeof(hdr.offset));
	write(fd, ((char *)&hdr.dib_header_size), sizeof(hdr.dib_header_size));
	write(fd, ((char *)&hdr.width_px), sizeof(hdr.width_px));
	write(fd, ((char *)&hdr.height_px), sizeof(hdr.height_px));
	write(fd, ((char *)&hdr.num_planes), sizeof(hdr.num_planes));
	write(fd, ((char *)&hdr.bpp), sizeof(hdr.bpp));
	write(fd, ((char *)&hdr.compression), sizeof(hdr.compression));
	write(fd, ((char *)&hdr.image_size_bytes), sizeof(hdr.image_size_bytes));
	write(fd, ((char *)&hdr.x_resolution_ppm), sizeof(hdr.x_resolution_ppm));
	write(fd, ((char *)&hdr.y_resolution_ppm), sizeof(hdr.y_resolution_ppm));
	write(fd, ((char *)&hdr.num_colors), sizeof(hdr.num_colors));
	write(fd, ((char *)&hdr.important_colors), sizeof(hdr.important_colors));
	ft_write_pixmap(img, fd);
	close(fd);
}

int			exit_cl(void)
{
	exit(0);
	return(0);
}

void		ft_launch_game(t_config cfg)
{
	t_player		one;
	t_img			img;
	t_prm_pkg		pkg;
	t_pos_lst		*obj_lst;

	one = ft_preset_player(&cfg);
	img = ft_preset_img(&cfg);
	obj_lst = ft_load_obj(cfg.obj_list);
	pkg = ft_pkg_prm(&cfg, &img, &one, &obj_lst);
	pkg.z_buffer = malloc(sizeof(float) * img.img_width + 1);
	ft_render_screen((void *)&pkg);
//	printf("%x, ", (unsigned char)*img.img_data);
//	printf("lol\n");
//	printf("%x, ", (unsigned char)*(img.img_data + 1));
//	printf("%x, ", (unsigned char)*(img.img_data + 2));
//	printf("%x\n", (unsigned char)*(img.img_data + 3));
	if (!cfg.mask)
	{
		ft_render_screen((void *)&pkg);
		ft_export_bmp(&img);
		ft_escape_game(&pkg);
	}
	mlx_hook(img.win_ptr, 17, 0, exit_cl, NULL);
//	mlx_hook(img.win_ptr, 17, 0, &ft_escape_game, &pkg);
//	mlx_hook(img.win_ptr, 2, 1, ft_get_key, &pkg);
	mlx_loop_hook(img.mlx_ptr, ft_render_screen, &pkg);
	mlx_loop(img.mlx_ptr);
	mlx_destroy_image(img.mlx_ptr, img.img_ptr);
	mlx_destroy_window(img.mlx_ptr, img.win_ptr);
	free(img.mlx_ptr);
}

int		main(int ac, char **av)
{
	t_file_data		fdata;
	t_config		setup_cfg;

	fdata = ft_preset_fdata(ac, av);
	setup_cfg = ft_get_config(&fdata);
	ft_add_map(&setup_cfg, &fdata);
	ft_wipe_file_data(&fdata);
	if (ac > 2)
		if (ft_strequ(av[2], "--save"))
				setup_cfg.mask = 0;
	ft_launch_game(setup_cfg);
	ft_print_fdata(&fdata);
	ft_print_cfg(&setup_cfg);
	ft_wipe_cfg(&setup_cfg);
	return (0);
}
