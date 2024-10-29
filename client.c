/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:16 by marvin            #+#    #+#             */
/*   Updated: 2024/10/29 20:28:40 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"

#include <signal.h>
#include <unistd.h>

volatile t_client_state	g_cli;

// NOTE: Check `man sigaction` for more info on signal handlers.
static void	handle_handshake(int sig)
{
	(void)sig;
	g_cli.sig_handshake = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
	{
		return (1);
	}
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_handshake;
	sigaction(SIGUSR1, &sa, NULL);
	ft_atoi(&pid, argv[1]);
	while (*argv[2])
	{
		g_cli.bit_char = *argv[2];
		while (g_cli.bit_count < 8)
		{
			if ((g_cli.bit_char >> 7) & 1)
			{
				kill(pid, SIGUSR2);
			}
			else
			{
				kill(pid, SIGUSR1);
			}
			while (!g_cli.sig_handshake)
			{
				pause();
			}
			++g_cli.bit_count;
			g_cli.bit_char <<= 1;
			g_cli.sig_handshake = 0;
		}
		++argv[2];
		g_cli.bit_count = 0;
	}
	return (0);
}
