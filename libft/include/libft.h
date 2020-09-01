/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:38:45 by iguidado          #+#    #+#             */
/*   Updated: 2020/04/23 19:16:22 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>

/*
**	Fonction memoire brut
*/
void					*ft_memset(void	*b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memccpy(void *dest, const void *src, int c,
	size_t n);
void					*ft_memmove(void *dest, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);

/*
**	charactere processing
*/
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
char					ft_toupper(int c);
char					ft_tolower(int c);

int						ft_isset(const char *set, char c);
int						ft_isindex(const char *set, char c);

/*
**	String processing
*/
size_t					ft_strlen(const char *s);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(const char *haystack, const char *needle,
	size_t len);

/*
**	String modification
*/
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlcat(char *dest, const char *src, size_t size);

/*
**	String Creation
*/
void					*ft_calloc(size_t count, size_t size);
char					*ft_strdup(const char *s1);
char					*ft_substr(char const *s, unsigned int start,
	size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s1, char const *set);
char					**ft_split(char const *s, char c);
char					*ft_strmapi(char const *s,
	char (*f)(unsigned int, char));

/*
** 	Transtypage
*/
int						ft_atoi(const char *str);
char					*ft_itoa(int n);

/*
**	fd write
*/
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);

/*
**	print simple data (char, int, char * -o [], void *)
*/
void					ft_putchar(char c);
void					ft_putstr(char *str);
void					ft_putendl(char *str);
void					ft_putnbr(int nbr);
void					ft_putnbr_base(int nbr, char *base);
void					ft_putstr_non_printable(char *str);
void					ft_print_memory(void *addr, int size);

/*
**	print table (char**, int *, char *, void *)
*/

void					ft_print_tab(char **tab);
void					ft_print_iarray(int **iarray, int size);
/*
**	Tab manipulation (char **)
*/
void					ft_free_tab(char ***tab);
int						ft_tabadd_back(char ***tab, char *str);

/*
**	BitWise
*/

char					ft_isbit(char *ref, char token);
char					ft_ismsk(char *ref, char *tokens);

/*
**	Linked list 101
*/

typedef struct s_list	t_list;
struct					s_list
{
	void		*content;
	t_list		*next;
};

t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **alst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **alst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst,
	void *(*f)(void *), void (*del)(void *));

/*
**	Math
*/
int						ft_abs(int nbr);

/*
**	char		*ft_strcpy(char *dest, char *src);
**	char		*ft_strcat(char *dest, const char *src);
**	void		*ft_memalloc(size_t size);
**	void		ft_memdel(void **ap);
**	char		*ft_strmap(char const *s, char (*f)(char));
**	char		*ft_strnew(size_t size);
**	void		ft_strclr(char *s);
**	void		ft_strdel(char **as);
**	void		ft_striter(char *s, void (*f)(char *));
**	void		ft_striteri(char *s, void (*f)(unsigned int, char *));
**	int			ft_strequ(char const *s1, char const *s2);
**	int			ft_strnequ(char const *s1, char const *s2, size_t n);
**	int			ft_strcmp(const char *s1, const char *s2);
**	void		ft_putchar(char c);
**	void		ft_putstr(char const *s);
**	void		ft_putendl(char const *s);
**	void		ft_putnbr(int n);
**	int			ft_strcmp(const char *s1, const char *s2);
**	char		*ft_strcpy(char *dest, char *src);
**	char		*ft_strncpy(char *dest, const char *src, size_t n);
**	char		*ft_strcat(char *dest, const char *src);
**	char		*ft_strncat(char *dest, const char *src, size_t n);
**	const char	*ft_strstr(const char *haystack, const char *needle);
**	int			ft_atoi_base(char *str, char *base);
*/

#endif
