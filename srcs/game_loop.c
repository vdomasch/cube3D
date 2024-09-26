/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:27 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/26 13:12:48 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>


void	move_player(t_data * data, t_player *player)
{
	if (player->walk_dir == 1)
	{
		if (data->map.map[(int)(player->pos_y + player->dir_y * player->move_speed)][(int)player->pos_x] != '1')
			player->pos_y += player->dir_y * player->move_speed;
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_x * player->move_speed)] != '1')
			player->pos_x += player->dir_x * player->move_speed;
	}
	if (player->walk_dir == -1)
	{
		if (data->map.map[(int)(player->pos_y - player->dir_y * player->move_speed )][(int)player->pos_x] != '1')
			player->pos_y -= player->dir_y * player->move_speed;
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_x * player->move_speed)] != '1')
			player->pos_x -= player->dir_x * player->move_speed;
	}
	if (player->strafe_dir == -1)
	{
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_y * player->move_speed)] != '1')
			player->pos_x += player->dir_y * player->move_speed;
		if (data->map.map[(int)(player->pos_y - player->dir_x * player->move_speed)][(int)player->pos_x] != '1')
			player->pos_y -= player->dir_x * player->move_speed;
	}
	if (player->strafe_dir == 1)
	{
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_y * player->move_speed)] != '1')
			player->pos_x -= player->dir_y * player->move_speed;
		if (data->map.map[(int)(player->pos_y + player->dir_x * player->move_speed)][(int)player->pos_x] != '1')
			player->pos_y += player->dir_x * player->move_speed;
	}
	(void)data;
}

void	rotate_player(t_data *data, t_player *player)
{
	if (player->turn_dir == 1)
	{
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-player->rot_speed) - player->dir_y * sin(-player->rot_speed);
		player->dir_y = old_dir_x * sin(-player->rot_speed) + player->dir_y * cos(-player->rot_speed);
		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-player->rot_speed) - player->plane_y * sin(-player->rot_speed);
		player->plane_y = old_plane_x * sin(-player->rot_speed) + player->plane_y * cos(-player->rot_speed);
	}
	if (player->turn_dir == -1)
	{
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(player->rot_speed) - player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed) + player->dir_y * cos(player->rot_speed);
		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(player->rot_speed) - player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed) + player->plane_y * cos(player->rot_speed);
	}
	(void)data;
}


int	game_loop(t_data *data)
{
	
	if (data->player.walk_dir || data->player.strafe_dir)
		move_player(data, &data->player);
	if (data->player.turn_dir)
		rotate_player(data, &data->player);
	raycasting(data);
	return (0);
}