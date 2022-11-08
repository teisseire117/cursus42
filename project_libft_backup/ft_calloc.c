/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 05:39:03 by hateisse          #+#    #+#             */
/*   Updated: 2022/10/30 06:48:38 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_log_b2(size_t n)
{
	size_t	res;

	res = 0;
	while (n > 0)
	{
			n = n >> 1;
			res++;
	}
	return (res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*addr;

	if (!nmemb || !size || ft_log_b2(nmemb) + ft_log_b2(size) > LOG_SIZE_T)
		return (NULL);
	addr = malloc(size * nmemb);
	if (!addr)
		return (NULL);
	ft_bzero(addr, size * nmemb);
	return (addr);
}
