/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:46:07 by qbarron           #+#    #+#             */
/*   Updated: 2024/06/12 17:31:38 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	reset_variables(int *len_received, char **str, int *i)
{
	*len_received = 0;
	if (*str)
	{
		ft_putendl_fd(*str, 1);
		free(*str);
		*str = NULL;
	}
	*i = 0;
}

static void	receive_strlen(int *curr_bit, int *received, char **str, int s)
{
	static int	len_value = 0;

	if (s == SIGUSR2)
		len_value += ft_recursive_power(2, *curr_bit);
	if (*curr_bit == 31)
	{
		*received = 1;
		*str = ft_calloc(len_value + 1, sizeof(char));
		if (*str == NULL)
			return ;
		*curr_bit = 0;
		len_value = 0;
		return ;
	}
	(*curr_bit)++;
}

static void	receive_client_info(int signal)
{
	static int	char_value = 0;
	static int	current_bit = 0;
	static int	len_received = 0;
	static int	i = 0;
	static char	*final_str = NULL;

	if (!len_received)
		receive_strlen(&current_bit, &len_received, &final_str, signal);
	else
	{
		if (signal == SIGUSR2)
			char_value += ft_recursive_power(2, current_bit);
		if (current_bit == 7)
		{
			final_str[i++] = char_value;
			current_bit = 0;
			if (char_value == 0)
				return (reset_variables(&len_received, &final_str, &i));
			char_value = 0;
			return ;
		}
		current_bit++;
	}
}

int	main(void)
{
	int	id;

	id = (int)(getpid());
	ft_printf("Hellooooo\n", id);
	ft_printf("Here is the PID: %d\n", id);
	signal(SIGUSR1, receive_client_info);
	signal(SIGUSR2, receive_client_info);
	while (1)
		pause();
}
