/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hateisse <hateisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:30:01 by hateisse          #+#    #+#             */
/*   Updated: 2022/11/07 08:57:20 by hateisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

char	*_pf_convert_int(t_flag *flag, int n)
{
	char			*res;

	if (n == 0)
		flag->zero_value = 1;
	if (n < 0)
	{
		flag->is_positive = 0;
		res = ft_utoa(-n);
	}
	else
		res = ft_itoa(n);
	return (res);
}

char	*_pf_convert_unsigned_int(t_flag *flag, unsigned int n)
{
	if (n == 0)
		flag->zero_value = 1;
	return (ft_utoa(n));
}

char	*_pf_convert_char(t_flag *flag, unsigned char c)
{
	if (c == 0)
		flag->zero_value = 1;
	return (ft_ctos(c));
}

char	*_pf_convert_string(char *s)
{
	if (!s)
		return (ft_strdup("(null)"));
	return (ft_strdup(s));
}

char	*_pf_convert_perc(void)
{
	return (ft_ctos('%'));
}

char	*_pf_convert_addr(t_flag *flag, unsigned long n)
{
	char	*s;

	if (n == 0)
		flag->zero_value = 1;
	if (!n)
		return (ft_strdup("(nil)"));
	s = ft_ultobase(n, 16);
	return (s);
}

char	*_pf_convert_hex(t_flag *flag, unsigned int n)
{
	char	*s;

	if (n == 0)
		flag->zero_value = 1;
	s = ft_ultobase(n, 16);
	if (!s)
		return (NULL);
	if (flag->identifier == 'X')
		ft_strtoupper(s);
	return (s);
}

char	*_pf_convert_octal(t_flag *flag, unsigned int n)
{
	if (n == 0)
		flag->zero_value = 1;
	return (ft_ultobase(n, 8));
}

char	*_pf_convert_argument(t_flag *flag, va_list ap, char **s)
{
	char	*res;

	if (ft_strchr("di", flag->identifier))
		res = _pf_convert_int(flag, va_arg(ap, int));
	else if (ft_strchr("xX", flag->identifier))
		res = _pf_convert_hex(flag, va_arg(ap, unsigned int));
	else if (flag->identifier == 'o')
		res = _pf_convert_octal(flag, va_arg(ap, unsigned int));
	else if (flag->identifier == 'u')
		res = _pf_convert_unsigned_int(flag, va_arg(ap, unsigned int));
	else if (flag->identifier == 'c')
		res = _pf_convert_char(flag, va_arg(ap, int));
	else if (flag->identifier == 's')
		res = _pf_convert_string(va_arg(ap, char *));
	else if (flag->identifier == 'p')
		res = _pf_convert_addr(flag, va_arg(ap, unsigned long));
	else if (flag->identifier == '%')
		res = _pf_convert_perc();
	*s = res;
	return (res);
}

char	*_pf_add_hex_prefix(t_flag *flag, char **s)
{
	void	*addr;

	addr = *s;
	if (flag->identifier == 'p' && ft_strcmp(*s, "(nil)"))
		*s = ft_strjoin("0x", *s);
	if (addr != *s)
		free(addr);
	return (*s);
}

const char	*_pf_post_conversion_job(t_flag *flag, char *cvarg, size_t *total)
{
	const char	*flag_end_index;

	flag_end_index = flag->flag_end_index;
	if (flag->identifier == 'c' && flag->zero_value == 1)
		*total += 1;
	if (flag->identifier == 'c' && flag->zero_value == 1 && flag->minus != -1)
		write(1, "\0", 1);
	ft_putstr(cvarg);
	if (flag->identifier == 'c' && flag->zero_value == 1 && flag->minus == -1)
		write(1, "\0", 1);
	*total += ft_strlen(cvarg);
	free(cvarg);
	_pf_free_flag_structure(&flag);
	return (flag_end_index);
}

const char	*_pf_convert_main(const char *format, va_list ap, size_t *total)
{
	t_flag	*flag;
	char	*cvarg;

	flag = _pf_parse_flag_directives(format, ALLOC_MODE);
	if (!flag)
		return (NULL);
	cvarg = NULL;
	if (!_pf_convert_argument(flag, ap, &cvarg)
		|| !_pf_add_precision(flag, &cvarg)
		|| !_pf_add_hex_prefix(flag, &cvarg)
		|| !_pf_add_minus_sign_back(flag, &cvarg)
		|| !_pf_add_flag_characters_options(flag, &cvarg)
		|| !_pf_add_padding(flag, &cvarg))
	{
		_pf_free_flag_structure(&flag);
		if (cvarg)
			free(cvarg);
		return (NULL);
	}
	return (_pf_post_conversion_job(flag, cvarg, total));
}
