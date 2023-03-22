/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:38:06 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/22 16:05:30 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_is_c(char symbol, char c)
{
	if (symbol == c)
		return (1);
	return (0);
}

static int	ft_c_w(char *str, char c)
{
	int	word;

	word = 0;
	while (*str)
	{
		while (ft_is_c(*str, c))
			str++;
		if (!ft_is_c(*str, c) && *str)
			word++;
		while (!ft_is_c(*str, c) && *str)
			str++;
	}
	return (word);
}

static char	*ft_word_dup(char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!(word))
		return (NULL);
	word[i] = 0;
	while (i-- > 0)
		word[i] = str[i];
	return (word);
}

static void	*ft_clear_heap(char **wordlist, int index)
{
	while (--index >= 0)
	{
		free(wordlist[index]);
		wordlist[index] = NULL;
	}
	free(wordlist);
	return (wordlist = NULL);
}

char	**ft_split(char *s, char c)
{
	char	**wordlist;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	wordlist = (char **)(malloc(sizeof(char *) * (ft_c_w(s, c) + 1)));
	if (!(wordlist))
		return (NULL);
	while (*s)
	{
		while (ft_is_c(*s, c) && *s)
			s++;
		if (!ft_is_c(*s, c) && *s)
		{
			wordlist[i] = ft_word_dup(s, c);
			if (!(wordlist))
				return (ft_clear_heap(wordlist, i));
			i++;
		}
		while (!ft_is_c(*s, c) && *s)
			s++;
	}
	wordlist[i] = NULL;
	return (wordlist);
}
