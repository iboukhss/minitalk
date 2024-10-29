/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:22:18 by iboukhss          #+#    #+#             */
/*   Updated: 2024/10/29 20:25:51 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stddef.h>

int		ft_atoi(int *out_val, const char *str);
int		ft_printf(const char *format, ...);
void	*ft_memset(void *s, int c, ptrdiff_t n);

#endif
