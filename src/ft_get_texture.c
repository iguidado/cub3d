#include "cub3d.h"

int			ft_get_no_text(t_config *cfg, t_file_data *fdata)
{
	int tmp_fd;

	if (cfg->mask & FLAG_NO)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	if ((tmp_fd = open(fdata->paramlist[1], O_RDONLY)) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	cfg->no_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_NO);
}

int			ft_get_so_text(t_config *cfg, t_file_data *fdata)
{
	int tmp_fd;

	if (cfg->mask & FLAG_SO)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	if ((tmp_fd = open(fdata->paramlist[1], O_RDONLY)) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	cfg->so_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_SO);
}

int			ft_get_we_text(t_config *cfg, t_file_data *fdata)
{
	int tmp_fd;

	if (cfg->mask & FLAG_WE)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	if ((tmp_fd = open(fdata->paramlist[1], O_RDONLY)) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	cfg->we_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_WE);
}

int			ft_get_ea_text(t_config *cfg, t_file_data *fdata)
{
	int tmp_fd;

	if (cfg->mask & FLAG_EA)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	if ((tmp_fd = open(fdata->paramlist[1], O_RDONLY)) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	cfg->ea_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_EA);
}

int			ft_get_spri_text(t_config *cfg, t_file_data *fdata)
{
	int tmp_fd;

	if (cfg->mask & FLAG_SPRI)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	if ((tmp_fd = open(fdata->paramlist[1], O_RDONLY)) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	cfg->spri_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_SPRI);
}
