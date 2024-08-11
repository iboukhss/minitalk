/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:16 by marvin            #+#    #+#             */
/*   Updated: 2024/08/11 15:03:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

volatile int			sig_handshake;
volatile int			bit_count;
volatile unsigned char	bit_char;

void	handle_handshake(int sig)
{
	sig_handshake = 1;
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
		return (1);
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_handshake;
	sigaction(SIGUSR1, &sa, NULL);
	write(STDOUT_FILENO, "Ok!\n", 4);
	pid = atoi(argv[1]);
	while (*argv[2])
	{
		bit_char = *argv[2];
		while (bit_count < 8)
		{
			if ((bit_char >> 7) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (!sig_handshake)
			{
				pause();
			}
			++bit_count;
			bit_char <<= 1;
			sig_handshake = 0;
		}
		++argv[2];
		bit_count = 0;
	}
	return (0);
}
