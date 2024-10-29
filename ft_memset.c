/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:03:06 by iboukhss          #+#    #+#             */
/*   Updated: 2024/10/29 20:24:51 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// NOTE: Casting to unsigned char is considered more "standard" for whatever
// reason.

void	*ft_memset(void *s, int c, ptrdiff_t n)
{
	void	*src;

	src = s;
	while (n > 0)
	{
		*(char *)s++ = (unsigned char)c;
		n--;
	}
	return (src);
}
