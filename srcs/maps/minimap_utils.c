/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:55:57 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/08 14:43:05 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

void	init_minimap(t_data *data)
{
	data->mmap.size = HEIGHT / 3;
	data->mmap.sqr_size = data->mmap.size / 7;
	data->mmap.sqr_mid = data->mmap.sqr_size / 2;
	data->mmap.sqr_player_start = data->mmap.sqr_size / 3;
	data->mmap.sqr_player_end = data->mmap.sqr_size * 2 / 3;
	data->mmap.sqr_player_draw_position = data->mmap.sqr_size * 3 + 1;
	data->mmap.pos = data->mmap.sqr_size * 3;
	data->mmap.l_start_width = data->mmap.sqr_size * 3 / 7;
	data->mmap.l_end_width = data->mmap.sqr_size * 4 / 7;
	data->mmap.l_start_len = data->mmap.sqr_size / 8;
	data->mmap.l_end_len = data->mmap.sqr_size * 7 / 8;
}
