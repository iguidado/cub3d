/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:23:00 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 01:05:44 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "gl_parse_data.h"
#include "gl_error.h"

void	ft_print_id_mask(t_config *cfg)
{
	int i;

	i = 0;
	while (i < ID_NB)
	{
		ft_putstr_fd(g_id_tab[i].id, 2);
		if (cfg->mask & (1 << i))
			ft_putchar_fd('*', 2);
		else
			ft_putchar_fd('x', 2);
		ft_putchar_fd(' ', 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
}

void	ft_print_error_line(t_file_data *fdata)
{
	char *tmp;

	tmp = ft_itoa(fdata->line_nb);
	ft_putstr_fd("Line [", 2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	ft_putstr_fd("] \"", 2);
	ft_putstr_fd(fdata->line, 2);
	ft_putstr_fd("\"\n", 2);
}

void	ft_manage_run_error(int errnum, t_prm_pkg *cub)
{
	ft_putendl_fd("Error", 2);
	if (errnum == ERROR_SYSCALL)
	{
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (errnum < ERROR_SYSCALL)
	{
		ft_putendl_fd(g_error[errnum].message, 2);
	}
	ft_wipe_cfg(cub->cfg);
	ft_wipe_obj(&cub->obj_lst);
	if (cub->one)
		free(cub->one);
	if (cub->img)
	{
		ft_wipe_img(cub->img);
		free(cub->img);
		if (cub->z_buffer)
			free(cub->z_buffer);
	}
	exit(EXIT_FAILURE);
}

void	ft_manage_parse_error(int errnum, t_config *cfg, t_file_data *fdata)
{
	ft_putendl_fd("Error", 2);
	if (errnum == ERROR_SYSCALL)
		ft_putendl_fd(strerror(errno), 2);
	else if (errnum < ERROR_SYSCALL)
	{
		if (errnum >= ERROR_ID_CFG && errnum <= ERROR_MISS_MAP)
		{
			ft_print_error_line(fdata);
			if (errnum < ERROR_MISS_MAP)
				ft_print_id_mask(cfg);
		}
		ft_putendl_fd(g_error[errnum].message, 2);
	}
	if (cfg)
		ft_wipe_cfg(cfg);
	if (fdata)
		ft_wipe_file_data(fdata);
	exit(EXIT_FAILURE);
}
