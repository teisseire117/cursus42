/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 05:27:48 by hateisse          #+#    #+#             */
/*   Updated: 2022/10/30 05:27:49 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end_i;

	while (ft_strchr(set, *s1) && *s1)
		s1++;
	end_i = 0;
	while (!ft_strchr(set, s1[end_i]) && s1[end_i])
		end_i++;
	return (ft_substr(s1, 0, end_i));
}
