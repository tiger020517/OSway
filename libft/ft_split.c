/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 06:26:02 by junhykim          #+#    #+#             */
/*   Updated: 2024/10/20 08:51:03 by junhykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

static int	ft_count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_putword(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_words(char const *s, char c, char **s2, int num_words)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < num_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		s2[word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!s2[word])
			return (free_array(s2, word));
		ft_putword(s2[word], s, i, word_len);
		word_len = 0;
		word++;
	}
	s2[word] = 0;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num_words;

	if (!s)
		return (0);
	num_words = ft_count_words(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!s2)
		return (0);
	s2 = ft_split_words(s, c, s2, num_words);
	return (s2);
}

/* #include "libft.h"

static int		punch(char const *s, char *tmp, char c);
static void		feel_it(char **go, char *tmp, int getsu);
static void		kill_it(char **go, int getsu);

char	**ft_split(char const *s, char c)
{
	char	**go;
	char	*tmp;
	int		getsu;

	tmp = ft_strdup(s);
	getsu = punch(s, tmp, c);
	go = (char **)malloc(sizeof(char *) * (getsu + 2));
	if (!go)
		return (NULL);
	feel_it(go, tmp, getsu);
	return (go);
}

static int	punch(char const *s, char *tmp, char c)
{
	int	idx;
	int	tidx;
	int	getsu;

	idx = 0;
	tidx = 0;
	getsu = 0;
	while (s[idx])
	{
		if (s[idx] == c)
		{
			if (idx != 0 && s[idx - 1] != c)
				tmp[tidx] = '\0';
			idx++;
			getsu++;
		}
		tmp[tidx++] = s[idx++];
	}
	tmp[tidx] = '\0';
	return (getsu);
}

static void	feel_it(char **go, char *tmp, int getsu)
{
	int	idx;
	int	tidx;
	int	inidx;

	idx = 0;
	tidx = 0;
	while (idx < getsu)
	{
		go[idx] = (char *)malloc(ft_strlen(tmp) + 1);
		if (!go[idx])
		{
			kill_it(go, getsu);
			return ;
		}
		inidx = 0;
		while (tmp[tidx])
			go[idx][inidx++] = tmp[tidx++];
		idx++;
		tidx++;
	}
	go[idx] = '\0';
}

static void	kill_it(char **go, int getsu)
{
	while (getsu > 0)
	{
		free(go[getsu - 1]);
	}
	free(go[getsu]);
}
 */