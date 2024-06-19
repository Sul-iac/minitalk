/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:45:59 by qbarron           #+#    #+#             */
/*   Updated: 2024/06/12 17:30:14 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	check_errors(char **argv, int argc)
{
	int	i;

	i = -1;
	if (argc != 3)
	{
		ft_printf("Wrong type of arguments!\n");
		return (-1);
	}
	while (argv[1][++i])
	{
		if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
		{
			ft_printf("Wrong type of arguments!\n");
			return (-1);
		}
	}
	return (0);
}

static void	send_next_char(char c, int pid)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(WAIT_TIME);
	}
}

static void	ft_strlen_bit_by_bit(int pid, int len)
{
	int	i;

	i = -1;
	while (++i < 32)
	{
		if (len & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		usleep(WAIT_TIME);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		pid;
	int		len;
	char	*string_to_send;

	if (check_errors(argv, argc))
		return (-1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (-1);
	string_to_send = argv[2];
	len = ft_strlen(string_to_send);
	i = -1;
	ft_strlen_bit_by_bit(pid, len);
	while (string_to_send[++i])
		send_next_char(string_to_send[i], pid);
	send_next_char('\0', pid);
}
