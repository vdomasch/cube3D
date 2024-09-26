/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:27 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/26 16:11:45 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>


void	move_player(t_data * data, t_player *player)
{
	if (player->walk_dir == 1)
	{
		if (data->map.map[(int)(player->pos_y + player->dir_y * (player->move_speed + 0.28))][(int)player->pos_x] != '1')
			player->pos_y += player->dir_y * player->move_speed;
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_x * (player->move_speed + 0.28))] != '1')
			player->pos_x += player->dir_x * player->move_speed;
	}
	if (player->walk_dir == -1)
	{
		if (data->map.map[(int)(player->pos_y - player->dir_y * (player->move_speed + 0.28))][(int)player->pos_x] != '1')
			player->pos_y -= player->dir_y * player->move_speed;
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_x * (player->move_speed + 0.28))] != '1')
			player->pos_x -= player->dir_x * player->move_speed;
	}
	if (player->strafe_dir == -1)
	{
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_y * (player->move_speed + 0.28))] != '1')
			player->pos_x += player->dir_y * player->move_speed;
		if (data->map.map[(int)(player->pos_y - player->dir_x * (player->move_speed + 0.28))][(int)player->pos_x] != '1')
			player->pos_y -= player->dir_x * player->move_speed;
	}
	if (player->strafe_dir == 1)
	{
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_y * (player->move_speed + 0.28))] != '1')
			player->pos_x -= player->dir_y * player->move_speed;
		if (data->map.map[(int)(player->pos_y + player->dir_x * (player->move_speed + 0.28))][(int)player->pos_x] != '1')
			player->pos_y += player->dir_x * player->move_speed;
	}
	(void)data;
}

void	rotate_player(t_player *player)
{
	double old_dir_x;
	double old_plane_x;
	double rotation_amount = player->rot_speed;
	
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if (player->turn_dir == 1)
	{
		player->dir_x = player->dir_x * cos(-rotation_amount) - player->dir_y * sin(-rotation_amount);
		player->dir_y = old_dir_x * sin(-rotation_amount) + player->dir_y * cos(-rotation_amount);
		player->plane_x = player->plane_x * cos(-rotation_amount) - player->plane_y * sin(-rotation_amount);
		player->plane_y = old_plane_x * sin(-rotation_amount) + player->plane_y * cos(-rotation_amount);
	}
	if (player->turn_dir == -1)
	{
		player->dir_x = player->dir_x * cos(rotation_amount) - player->dir_y * sin(rotation_amount);
		player->dir_y = old_dir_x * sin(rotation_amount) + player->dir_y * cos(rotation_amount);
		player->plane_x = player->plane_x * cos(rotation_amount) - player->plane_y * sin(rotation_amount);
		player->plane_y = old_plane_x * sin(rotation_amount) + player->plane_y * cos(rotation_amount);
	}
}

void rotate_player_mouse(t_player *player, double x)
{
	double rotation_amount = player->rot_speed * x * 0.05;

	double old_dir_x = player->dir_x;
	double old_plane_x = player->plane_x;

	player->dir_x = player->dir_x * cos(rotation_amount) - player->dir_y * sin(rotation_amount);
	player->dir_y = old_dir_x * sin(rotation_amount) + player->dir_y * cos(rotation_amount);
	player->plane_x = player->plane_x * cos(rotation_amount) - player->plane_y * sin(rotation_amount);
	player->plane_y = old_plane_x * sin(rotation_amount) + player->plane_y * cos(rotation_amount);
}

int	game_loop(t_data *data)
{
	int x;
	int y;
	
	int x = 0;
	int y = 0;
	if (data->player.walk_dir || data->player.strafe_dir)
		move_player(data, &data->player);
	if (data->player.turn_dir)
		rotate_player(&data->player);
	if (data->move_mouse)
	{
		mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
		rotate_player_mouse(&data->player, (x - data->res_x / 2));
		if (x > data->res_x / 2 + 1 || x < data->res_x / 2 - 1 || y > data->res_y / 2 + 1 || y < data->res_y / 2 - 1)
			mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->res_x / 2, data->res_y / 2);
	}
	raycasting(data);
	return (0);
}