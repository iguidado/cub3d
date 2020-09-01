/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:48:19 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 01:16:40 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	char		*ft_reverse_row(char *row)
**	{
**		int		i;
**		int		strlen;
**		char	*rev_str;
**
**		i = 0;
**		strlen = ft_strlen(row);
**		rev_str = malloc(sizeof(char) * (strlen + 1));
**		rev_str[strlen] = 0;
**		while (row[i])
**		{
**			rev_str[strlen - i - 1] = row[i];
**			i++;
**		}
**		return (rev_str);
**	}
**
**	int			ft_set_map(t_file_data *fdata, t_map *map)
**	{
**		map->map = ft_split(fdata->line, ' ');
**
**	}
**
**	Maybe to a manip malloc lib
**
**	  char		*ft_add_newline(char **str)
**	  {
**		char *new;
**		int strlen;
**
**		strlen = ft_strlen(*str);
**		if (!(new = (char *)malloc(sizeof(char) * (strlen + 2))))
**			return (NULL);
**		new[strlen + 1] = '\0';
**		new[strlen] = '\n';
**		while (strlen--)
**			new[strlen] = (*str)[strlen];
**		free(*str);
**		return (new);
**	  }
**
**	can replace  ft_isset, to see if it is more performant
**
**	char		ft_istile(char c)
**	{
**		if ((c >= '0' && c <= '2') || c == ' ')
**			return (1);
**		if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
**			return (2);
**		return (0);
**	}
**
**	Don't enter bad value, it will crash
*/

int			ft_add_row(char ***ptr_map, char *row)
{
	int		i;
	int		ret;
	char	**new;

	i = 0;
	if (*ptr_map)
	{
		while ((*ptr_map)[i])
			i++;
	}
	if (!(new = (char **)malloc(sizeof(char *) * (i + 2))))
		return (0);
	new[i + 1] = 0;
	new[i] = row;
	while (i--)
		new[i] = (*ptr_map)[i];
	if (*ptr_map)
		free(*ptr_map);
	*ptr_map = new;
	return (1);
}

void		ft_check_after_map(t_config *cfg, t_file_data *fdata)
{
	int	ret;

	if (!fdata->line)
		return ;
	if (!ft_line_is_empty(fdata->line))
		ft_manage_parse_error(ERROR_UNKWN_MAP, cfg, fdata);
	free(fdata->line);
	while ((ret = get_next_line(fdata->fd, &fdata->line)))
	{
		if (ret == -1)
			ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
		fdata->line_nb++;
		if (ft_line_is_map(fdata->line))
			ft_manage_parse_error(ERROR_EMPTY_MAP, cfg, fdata);
		if (!ft_line_is_empty(fdata->line))
			ft_manage_parse_error(ERROR_AFTER_MAP, cfg, fdata);
		free(fdata->line);
	}
}

void		ft_get_map(t_config *cfg, t_file_data *fdata)
{
	while (ft_line_is_map(fdata->line))
	{
		ft_add_row(&cfg->map.data, fdata->line);
		if (ft_strlen(fdata->line) > cfg->map.res.x)
			cfg->map.res.x = ft_strlen(fdata->line);
		if (get_next_line(fdata->fd, &fdata->line) == -1)
			ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
		fdata->line_nb++;
	}
}

void		ft_add_map(t_config *cfg, t_file_data *fdata)
{
	int			ret;

	while (!ft_line_is_map(fdata->line))
	{
		free(fdata->line);
		if ((ret = get_next_line(fdata->fd, &fdata->line)) == -1)
			ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
		else if (!ret)
			ft_manage_parse_error(ERROR_MISS_MAP, cfg, fdata);
		fdata->line_nb++;
	}
	ft_get_map(cfg, fdata);
	ft_check_after_map(cfg, fdata);
	if (!ft_equalize_row(&cfg->map))
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	ft_process_map(cfg, fdata);
	ft_check_map_data(cfg, fdata);
}
