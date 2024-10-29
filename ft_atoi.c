/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:03:19 by iboukhss          #+#    #+#             */
/*   Updated: 2024/10/29 16:23:48 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <errno.h>
#include <limits.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_overflow(int num, int digit)
{
	if (num < 0)
	{
		return (num < (INT_MIN + digit) / 10);
	}
	else
	{
		return (num > (INT_MAX - digit) / 10);
	}
}

static int	parse_int(int *out_val, const char *str, int sign)
{
	int	num;
	int	digit;

	num = 0;
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (is_overflow(num, digit))
		{
			return (ERANGE);
		}
		num *= 10;
		num += sign * digit;
		++str;
	}
	if (out_val != NULL)
	{
		*out_val = num;
	}
	return (0);
}

int	ft_atoi(int *out_val, const char *str)
{
	int	sign;

	sign = 1;
	while (ft_isspace(*str))
	{
		++str;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign = -1;
		}
		++str;
	}
	if (!ft_isdigit(*str))
	{
		return (EINVAL);
	}
	return (parse_int(out_val, str, sign));
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char tests[7][20] = {
		"0",
		"-2147483648",
		"2147483647",
		"2147483648",
		"-2147483649",
		"2147483646",
		"-2147483647",
	};
	int d, err;
	for (int i = 0; i < 7; i++)
	{
		err = ft_atoi(&d, tests[i]);
		printf("%11s: %11d, %s\n", tests[i], d, strerror(err));
	}
}
*/
