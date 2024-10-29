/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:16 by marvin            #+#    #+#             */
/*   Updated: 2024/10/29 23:51:46 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"

#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_ack_received;

static void	handle_ack(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_byte(int pid, int c)
{
	int				bit_count;
	unsigned char	bit_char;

	bit_char = c;
	bit_count = 0;
	while (bit_count < 8)
	{
		if ((bit_char >> 7) & 1)
		{
			kill(pid, SIGUSR2);
		}
		else
		{
			kill(pid, SIGUSR1);
		}
		while (!g_ack_received)
		{
			pause();
		}
		g_ack_received = 0;
		bit_char <<= 1;
		bit_count += 1;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;
	int					err;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <string>\n", argv[0]);
		return (1);
	}
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_ack;
	sigaction(SIGUSR1, &sa, NULL);
	err = ft_atoi(&pid, argv[1]);
	if (err || pid <= 0)
	{
		ft_printf("Invalid PID: %s\n", argv[1]);
		return (1);
	}
	while (*argv[2])
	{
		send_byte(pid, *argv[2]);
		argv[2]++;
	}
	return (0);
}
