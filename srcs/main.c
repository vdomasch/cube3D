/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:48:24 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:02 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc < 2)
	{
		ft_putstr_fd("Error\n Invlaid number of arguments\n", 2);
		return (1);
	}
	parsing(&data, argv);
	ft_putstr_fd("End!\n", 1);
	return (0);
}