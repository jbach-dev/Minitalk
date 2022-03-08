/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbach <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:39:40 by jbach             #+#    #+#             */
/*   Updated: 2022/02/03 17:39:43 by jbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_timeout = -1;

char	*ft_write(char buf[INT_MAX], int i, siginfo_t *info)
{
	write(1, buf, i);
	write(1, "\n", 1);
	buf[0] = '\0';
	kill(info->si_pid, SIGUSR1);
	return (buf);
}

char	*ft_def(char buf[INT_MAX], int i, int sig)
{
	buf[i] = buf[i] << 1;
	if (sig == SIGUSR1)
		buf[i] += 1;
	return (buf);
}

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit = 7;
	static int	i = 0;
	static char	buf[INT_MAX];

	(void)		*context;
	(void)		*info;
	g_timeout = 0;
	if (bit == 7)
		buf[i] = '\0';
	if (bit-- >= 0)
		ft_def(buf, i, sig);
	if (bit == -1)
	{
		bit = 7;
		if (buf[i] == '\0' || i == (INT_MAX - 1))
		{
			ft_write(buf, i, info);
			g_timeout = -1;
			i = 0;
		}
		else
			i++;
	}
}

void	ft_error(int argc)
{
	if (argc == 1)
	{
		ft_putstr_fd("PID : ", 1);
		ft_putnbr_fd(getpid(), 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		write(1, "Erreur d'arguments\n", 18);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void) argv;
	ft_error(argc);
	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	while (1)
	{
		if (g_timeout == 1000)
		{
			write(1, "Erreur Serveur\n", 14);
			exit(1);
		}
		usleep(128);
		g_timeout += (g_timeout != -1);
	}
	return (0);
}
