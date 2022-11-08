/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_add_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:24:01 by hateisse          #+#    #+#             */
/*   Updated: 2022/11/07 07:31:53 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		_pf_is_hex_shape(t_flag *flag)
{
	if (flag->zero_value != -1)
		return (0);
	if (flag->identifier == 'p')
		return (1);
	if (flag->hashtag != -1 && ft_strchr("xX", flag->identifier))
		return (1);
	return (0);
}

char	*_pf_build_precision(t_flag *flag, char *s)
{
	char	*res;
	size_t	len;

	if ((size_t)flag->v_precision <= ft_strlen(s))
		return (ft_strdup(""));
	len = (size_t)flag->v_precision - ft_strlen(s);
	res = ft_calloc(len + 1, sizeof(*res));
	if (!res)
		return (NULL);
	return (ft_memset(res, '0', len));
}

char	*_pf_add_precision_build(char **s, char *build)
{
	void	*addr;

	addr = *s;
	*s = ft_strjoin(build, *s);
	free(build);
	if (!*s)
		free(addr);
	return (*s);
}

char	*_pf_add_precision(t_flag *flag, char **s)
{
	void	*addr;
	char	*precision_build;

	addr = *s;
	if (flag->precision == -1)
		return (*s);
	else if (flag->v_precision == 0 && !ft_strcmp(*s, "0")
		&& ft_strchr("xXiodu", flag->identifier))
		*s = ft_strdup("");
	else if (flag->identifier == 's')
		*s = ft_substr(*s, 0, flag->v_precision);
	else if (ft_strchr("xXiodup", flag->identifier))
	{
		precision_build = _pf_build_precision(flag, *s);
		if (!precision_build || !_pf_add_precision_build(s, precision_build))
			return (NULL);
	}
	if (addr != *s)
		free(addr);
	return (*s);
}
