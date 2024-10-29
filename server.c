/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:07:01 by marvin            #+#    #+#             */
/*   Updated: 2024/10/29 23:50:42 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"

#include <unistd.h>
#include <signal.h>

static void	handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	static int				bit_count;
	static unsigned char	bit_char;

	(void)ucontext;
	bit_count += 1;
	if (sig == SIGUSR1)
	{
		bit_char = (bit_char << 1) | 0;
	}
	else if (sig == SIGUSR2)
	{
		bit_char = (bit_char << 1) | 1;
	}
	if (bit_count == 8)
	{
		write(STDOUT_FILENO, &bit_char, 1);
		bit_count = 0;
		bit_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("PID: %d\n", pid);
	ft_printf("Waiting for signal...\n");
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
