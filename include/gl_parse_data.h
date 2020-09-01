typedef int		(*id_ft)(t_config *, t_file_data *);

typedef struct	s_id_index
{
	char		*id;
	id_ft		fct;
}				t_id_index;

t_id_index	g_id_tab[] = 
{
	{"R", &ft_get_res},
	{"C", &ft_get_ceilar},
	{"R", &ft_get_floor},
	{"NO", &ft_get_no_text},
	{"SO", &ft_get_so_text},
	{"WE", &ft_get_we_text},
	{"EA", &ft_get_ea_text},
	{"S", &ft_get_spri_text}
};

