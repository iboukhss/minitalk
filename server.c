/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:07:01 by marvin            #+#    #+#             */
/*   Updated: 2024/10/28 19:48:19 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

volatile t_server_state	g_srv;

void	handle_sigusr(int sig, siginfo_t *info, void *vp)
{
	g_srv.client_pid = info->si_pid;
	++g_srv.bit_count;
	if (sig == SIGUSR1)
	{
		g_srv.bit_char = (g_srv.bit_char << 1) | 0;
	}
	else if (sig == SIGUSR2)
	{
		g_srv.bit_char = (g_srv.bit_char << 1) | 1;
	}
	if (g_srv.bit_count == 8)
	{
		write(STDOUT_FILENO, (const void *)&g_srv.bit_char, 1);
		g_srv.bit_count = 0;
		g_srv.bit_char = 0;
	}
	g_srv.sig_handshake = 1;
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
		if (g_srv.sig_handshake)
		{
			kill(g_srv.client_pid, SIGUSR1);
			g_srv.sig_handshake = 0;
		}
	}
	return (0);
}
