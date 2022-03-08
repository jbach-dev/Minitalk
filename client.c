/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbach <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:40:03 by jbach             #+#    #+#             */
/*   Updated: 2022/02/03 17:29:26 by jbach            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(int argc, char **argv)
{
	int	len_pid;
	int	len_pid_atoi;

	if (argc != 3 || ft_strlen(argv[2]) == 0)
	{
		write(1, "Erreur d'arguments\n", 19);
		exit(1);
	}
	len_pid = ft_strlen(argv[1]);
	len_pid_atoi = count_numbers(ft_atoi(argv[1]));
	if (len_pid != len_pid_atoi)
	{
		write(1, "Erreur du PID\n", 13);
		exit(1);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) >= INT_MAX || argv[1] == 0)
	{
		write(1, "Erreur du PID\n", 13);
		exit(1);
	}
}

void	ft_verif(int verif)
{
	if (verif)
	{
		write(1, "Erreur\n", 6);
		exit(1);
	}
}

void	signal_client(int pid, char *message)
{
	int			i;
	int			n;
	int			len_message;
	static int	verif;

	i = 0;
	len_message = ft_strlen(message);
	while (i <= len_message)
	{
		n = 7;
		while (n >= 0)
		{
			if (message[i] >> n & 1)
				verif = kill(pid, SIGUSR1);
			else
				verif = kill(pid, SIGUSR2);
			usleep(30);
			n--;
			ft_verif(verif);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	ft_error(argc, argv);
	signal_client(ft_atoi(argv[1]), argv[2]);
	return (0);
}
