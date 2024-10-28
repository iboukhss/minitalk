/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:00:21 by iboukhss          #+#    #+#             */
/*   Updated: 2024/10/28 19:37:52 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// NOTE: So, it seems like shifting a signed integer in the client triggers
// undefined behavior. I am revisiting this code 3 months later and I have
// no idea what most of it does.

typedef struct s_client_state
{
	int				bit_count;
	unsigned char	bit_char;
	int				sig_handshake;
}	t_client_state;

typedef struct s_server_state
{
	int		bit_count;
	char	bit_char;
	int		sig_handshake;
	int		client_pid;
}	t_server_state;

// Add libc functions here

// memset

// atoi

// printf?

#endif
