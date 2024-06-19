/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:39:45 by qbarron           #+#    #+#             */
/*   Updated: 2024/06/12 17:25:51 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	digits(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
	}
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

void	sign_and_convert(int n, int i, char *dup, int len)
{
	if (n < 0)
	{
		n *= -1;
		dup[i++] = '-';
	}
	dup[len] = '\0';
	while (n)
	{
		dup[--len] = n % 10 + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = digits(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (dup == NULL)
		return (NULL);
	sign_and_convert(n, i, dup, len);
	return (dup);
}
