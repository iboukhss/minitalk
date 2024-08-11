/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:07:01 by marvin            #+#    #+#             */
/*   Updated: 2024/08/11 06:34:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

volatile int	bit_count;
volatile char	bit_char;

volatile int	sig_handshake;
volatile int	client_pid;

void	handle_sigusr(int sig, siginfo_t *info, void *vp)
{
	client_pid = info->si_pid;
	++bit_count;
	if (sig == SIGUSR1)
	{
		write(STDOUT_FILENO, ".", 1);
		bit_char = (bit_char << 1) | 0;
	}
	else if (sig == SIGUSR2)
	{
		write(STDOUT_FILENO, "1", 1);
		bit_char = (bit_char << 1) | 1;
	}
	if (bit_count == 8)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, (const void *)&bit_char, 1);
		write(STDOUT_FILENO, "\n", 1);
		bit_count = 0;
		bit_char = 0;
	}
	sig_handshake = 1;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	printf("PID: %d\n", pid);
	printf("Waiting for signal...\n");
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
		if (sig_handshake)
		{
			kill(client_pid, SIGUSR1);
			sig_handshake = 0;
		}
	}
	return (0);
}
