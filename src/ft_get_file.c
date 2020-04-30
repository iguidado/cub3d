#ifdef BUFFER_SIZE
# undef BUFFER_SIZE
#endif
#define BUFFER_SIZE 640
#include "cub3d.h"

void	ft_clean_buf(char *buf)
{
		int i;

		i = 0;
		while (i < BUFFER_SIZE)
		{
			buf[i] = '\0';
			i++;
		}
}

char 	*ft_bufdup(char *buf)
{
		int		i;
		char	*new;

		i = 0;
		while (i < BUFFER_SIZE && buf[i])
			i++;
		if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		new[i] = '\0';
		while (i--)
			new[i] = buf[i];
		return (new);
}

char	*ft_bufjoin(char *buf, char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (i < BUFFER_SIZE && buf[i])
		i++;
	while (str[j])
		j++;
	if (!(new = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	new[i + j] = '\0';
	while (i--)
		new[j + i] = buf[i];
	while (j--)
		new[j] = str[j];
	return (new);
}

int		ft_cat_file(char *buf, char **file)
{
	char		*new;
	
	if (!*file)
	{
		if (!(*file = ft_bufdup(buf)))
			return (-1);
	}
	else
	{
		new = ft_bufjoin(buf, *file);
		free(*file);
		*file = new;
	}
	if (!*file)
		return (0);
	return (1);
}

int		ft_get_file(int fd, char **file)
{
	char	buf[BUFFER_SIZE];
	int		ret;

	ft_clean_buf(buf);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (!ft_cat_file(buf, file))
			perror(*file);
		ft_clean_buf(buf);
	}
	return (ret + 1);
}

/*
**	int		main(void)
**	{
**		int		fd;
**		char	*file;
**		char	**wordlist;
**	
**		fd = open("src/ft_get_file.c", O_RDONLY);
**		if (!(ft_get_file(fd, &file)))
**				perror("Can't get file");
**		printf("%s", file);
**		ft_putendl("----------------------------------");
**		wordlist = ft_split(file, '\n');
**		ft_print_tab(wordlist);
**		free(file);
**		close(fd);
**		return (0);
**	}
*/
