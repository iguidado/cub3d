#ifndef GL_ERROR
# define GL_ERROR

typedef struct	s_error
{
	int			errnum;
	char		*message;
}				t_error;

typedef void	(*error_ft)(int, t_config *, t_file_data *);

t_error	const g_error[] =
{
	{ERROR_NB_ARGS, "Wrong number of arguments."},
	{ERROR_INVALID_FILE, "Wrong file extension for configuration file "
	"(format must be \"*.cub\")."},
	{ERROR_INVALID_ARG, "Can't recognize second argument " 
	"(did you mean \"--save\" ?)."},
	{ERROR_ID_CFG, "configuration ID not recognized."},
	{ERROR_SYN_CFG, "Wrong syntax for configuration line."},
	{ERROR_LEX_CFG, "Lexical error on parameter's configuration line"},
	{ERROR_DUP_CFG, "configuration ID found twice."},
	{ERROR_MISS_CFG, "less configuration line than what is expected."},
	{ERROR_MISS_MAP, "Could'nt find the map."},
	{ERROR_OPEN_MAP, "Map have open boundaries."},
	{ERROR_UNKWN_MAP, "Map have unknown tiles inside."},
	{ERROR_EMPTY_MAP, "Map have empty line inside."},
	{ERROR_AFTER_MAP, "There is garbage information after map"},
	{ERROR_PLAYER_MAP, "Map have wrong number of player (should be 1)."},
	{ERROR_SPRI_MAP, "Map have wrong number of sprite (should be at least 1)."},
	{ERROR_MLX_INIT, "Connection with X failed."},
	{ERROR_MLX_NEW_WIN, "Failed to open new window."},
	{ERROR_MLX_NEW_IMG, "Failed to generate image."},
	{ERROR_MLX_SCREEN, "Failed to generate screen."},
};

#endif
