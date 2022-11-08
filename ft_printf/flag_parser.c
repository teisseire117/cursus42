/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 02:11:33 by hateisse          #+#    #+#             */
/*   Updated: 2022/11/07 05:50:31 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	_pf_parse_leading_symbol(const char **to_parse)
{
	if (**to_parse == '%')
	{
		*to_parse += 1;
		return (0);
	}
	return (1);
}

void	_pf_parse_flag_characters(const char **to_parse_addr, t_flag *flag)
{
	const char	*to_parse;

	to_parse = *to_parse_addr;
	while (ft_strchr("-+#0 " ,*to_parse))
	{
		if (*to_parse == '-')
			flag->minus = 1;
		else if (*to_parse == '+')
			flag->plus = 1;
		else if (*to_parse == '#')
			flag->hashtag = 1;
		else if (*to_parse == '0')
			flag->zero = 1;
		else if (*to_parse == ' ')
			flag->blank = 1;
		to_parse++;
	}
	*to_parse_addr = to_parse;
}

void	_pf_parse_width_specification(const char **to_parse_addr, t_flag *flag)
{
	if (ft_isdigit(**to_parse_addr))
	{
		flag->width = 1;
		errno = 0;
		flag->v_width = ft_strtol(*to_parse_addr, to_parse_addr, 10);
		if (errno || flag->v_width < 0 || flag->v_width >= INT_MAX - 32)
			flag->v_width = -1;
	}
}

void	_pf_parse_precision_specification(const char **to_parse_addr, t_flag *flag)
{
	if (**to_parse_addr == '.')
	{
		*to_parse_addr += 1;
		flag->precision = 1;
		errno = 0;
		flag->v_precision = ft_strtol(*to_parse_addr, to_parse_addr, 10);
		if (errno || flag->v_precision < 0 || flag->v_precision >= INT_MAX - 32)
			flag->v_precision = -1;
	}
}

int		_pf_parse_type_specifier(const char **to_parse, t_flag *flag)
{
	if (ft_strchr("ocspdiuxX%", **to_parse))
		flag->identifier = *(*to_parse++);
	else
		return (1);
	return (0);
}
