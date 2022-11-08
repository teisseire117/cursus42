/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:49:32 by hateisse          #+#    #+#             */
/*   Updated: 2022/11/07 05:59:04 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

size_t	_pf_print_then_advance(const char *format, size_t *total)
{
	size_t	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && _pf_parse_flag_directives(&format[i], NO_ALLOC_MODE))
			break ;
		(*total)++;
		i++;
	}
	ft_putnstr(format, i);
	return (i);
}

t_flag	*_pf_free_flag_structure(t_flag **flag)
{
	if (flag && *flag)
	{
		free(*flag);
		*flag = NULL;
	}
	return (*flag);
}

t_flag	*_pf_init_flag_structure(void)
{
	t_flag	*flag;

	flag = malloc(sizeof(*flag) * (1));
	if (!flag)
		return (NULL);
	flag->precision = -1;
	flag->width = -1;
	flag->v_precision = 0;
	flag->v_width = 0;
	flag->blank = -1;
	flag->minus = -1;
	flag->plus = -1;
	flag->zero = -1;
	flag->hashtag = -1;
	flag->identifier = -1;
	flag->is_positive = 1;
	flag->zero_value = -1;
	flag->flag_end_index = 0;
	return (flag);
}

t_flag	*_pf_parse_flag_directives(const char *to_parse, char mode)
{
	t_flag	*flag;

	flag = _pf_init_flag_structure();
	if (!flag)
		return (NULL);
	if (_pf_parse_leading_symbol(&to_parse))
	{
		_pf_free_flag_structure(&flag);
		return (NULL);
	}
	if (*to_parse != '%')
	{
		_pf_parse_flag_characters(&to_parse, flag);
		_pf_parse_width_specification(&to_parse, flag);
		_pf_parse_precision_specification(&to_parse, flag);
	}
	if (_pf_parse_type_specifier(&to_parse, flag))
	{
		_pf_free_flag_structure(&flag);
		return (NULL);
	}
	flag->flag_end_index = to_parse + 1;
	if (mode == NO_ALLOC_MODE)
		free(flag);
	return (flag);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	total;

	va_start(ap, format);
	total = 0;
	while (*format)
	{
		format += _pf_print_then_advance(format, &total);
		if (*format == '%')
		{
			format = _pf_convert_main(format, ap, &total);
			if (!format)
			{
				va_end(ap);
				return (-1);
			}
		}
	}
	va_end(ap);
	return (total);
}
