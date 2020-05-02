#include "cub3d.h"

int				ft_get_res(t_config *cfg, t_file_data *fdata)
{
	if (cfg->mask & FLAG_RES)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 3)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata); 
	if (!ft_str_isdigit(fdata->paramlist[1]) || !ft_str_isdigit(fdata->paramlist[2]))
		ft_manage_parse_error(ERROR_LEXICAL, cfg, fdata);
	cfg->screen_width = ft_atoi(fdata->paramlist[1]);
	cfg->screen_height = ft_atoi(fdata->paramlist[2]);
	return (FLAG_RES);
}

int			ft_get_ceilar(t_config *cfg, t_file_data *fdata)
{
	int i;
	int nbr;

	if (cfg->mask & FLAG_CEIL)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata); 
	if (!ft_str_is_colorcode(fdata->paramlist[1]))
		ft_manage_parse_error(ERROR_LEXICAL, cfg, fdata);
	i = 0;
	cfg->ceilar_color = 0;
	while (fdata->paramlist[1][i])
	{
		nbr = 0;
		while (ft_isdigit(fdata->paramlist[1][i]))
		{
			nbr = (nbr * 10) + (fdata->paramlist[1][i] - '0');
			i++;
		}
		cfg->ceilar_color = (cfg->ceilar_color << 8) + nbr;
		if (fdata->paramlist[1][i] == ',')
			i++;
	}
	return (FLAG_CEIL);
}

int			ft_get_floor(t_config *cfg, t_file_data *fdata)
{
	int i;
	int nbr;

	if (cfg->mask & FLAG_FLOOR)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata); 
	if (!ft_str_is_colorcode(fdata->paramlist[1]))
		ft_manage_parse_error(ERROR_LEXICAL, cfg, fdata);
	i = 0;
	cfg->floor_color = 0;
	while (fdata->paramlist[1][i])
	{
		nbr = 0;
		while (ft_isdigit(fdata->paramlist[1][i]))
		{
			nbr = (nbr * 10) + (fdata->paramlist[1][i] - '0');
			i++;
		}
		if (nbr > 255)
			ft_manage_parse_error(ERROR_LEXICAL, cfg, fdata);
		cfg->floor_color = (cfg->floor_color << 8) + nbr;
		i++;
	}
	return (FLAG_FLOOR);
}
