#ifndef CONFIG_H
# define CONFIG_H
# define FLAG_STR "RNSOEsFC"

typedef struct	s_config
{
	unsigned char	msk;
	int				width;
	int				height;
	int				ceilar_color;
	int				floor_color;
	int				no_text;
	int				so_text;
	int				ea_text;
	int				we_text;
	int				spri_text;
}				t_config;

t_config	ft_parse_cub(char *cub_file);
int			ft_get_res(int *width, int *height, char *line);

#endif
