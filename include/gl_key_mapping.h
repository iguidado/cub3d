#ifndef GL_KEY_MAPPING
# define GL_KEY_MAPPING

typedef struct	s_key_mapper
{
	int	key;
	int	input;
}				t_key_mapper

t_key_mapper const	g_key_map
{
	{KEY_W, INPUT W},
	{KEY_A, INPUT A},
	{KEY_S, INPUT S},
	{KEY_D, INPUT D},
	{KEY_LEFT, INPUT LEFT},
	{KEY_RIGHT, INPUT RIGHT},
	{KEY_ESC, INPUT ESC},
};

#endif
