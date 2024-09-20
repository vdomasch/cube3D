/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:28:39 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/20 14:12:21 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	long int	number;
	size_t		i;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	while (str[i] != ',' || str[i] != '\n')
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (-1);
		number = (number * 10) + (str[i++] - 48);
		if (number > 2147483647 && sign > 0)
			return (-1);
		if (number > 2147483648 && sign < 0)
			return (-1);
	}
	return (number * sign);
}
