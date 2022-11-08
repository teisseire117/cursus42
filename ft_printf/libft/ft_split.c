/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 05:26:11 by hateisse          #+#    #+#             */
/*   Updated: 2022/10/30 05:26:12 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(char const *s, char c)
{
	size_t	tabs;
	char	in_tab;

	tabs = 0;
	in_tab = 0;
	while (*s)
	{
		if (!in_tab && *s != c)
		{
			in_tab = 1;
			tabs++;
		}
		else if (in_tab && *s == c)
			in_tab = 0;
		s++;
	}
	return (tabs);
}

static char	*copy_until_then_advance(char **res, char **s, char c)
{
	size_t	len;

	len = ft_strchrnul(*s, c) - *s;
	*res = ft_calloc(len + 1, sizeof(**res));
	if (!*res)
	{
		ft_strsfree(res);
		return (NULL);
	}
	ft_strlcpy(*res, *s, len + 1);
	*s += len;
	return (*s);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	words;

	words = count_words(s, c);
	res = ft_calloc(words + 1, sizeof(*res));
	if (!res)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			copy_until_then_advance(res++, (char **)&s, c);
			if (!s)
				return (NULL);
		}
	}
	return (res - words);
}
