/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:44:27 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/03 14:32:20 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>


void	move_player(t_data *data, t_player *player)
{
	if (player->walk_dir == 1)
	{
		if (data->map.map[(int)(player->pos_y + player->dir_y * (player->move_speed + 0.28))][(int)player->pos_x] != '1'
			&& data->map.map[(int)(player->pos_y + player->dir_y * (player->move_speed + 0.28))][(int)player->pos_x] != 'c')
			player->pos_y += player->dir_y * player->move_speed;
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_x * (player->move_speed + 0.28))] != '1'
			&& data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_x * (player->move_speed + 0.28))] != 'c')
			player->pos_x += player->dir_x * player->move_speed;
	}
	if (player->walk_dir == -1)
	{
		if (data->map.map[(int)(player->pos_y - player->dir_y * (player->move_speed + 0.28))][(int)player->pos_x] != '1'
			&& data->map.map[(int)(player->pos_y - player->dir_y * (player->move_speed + 0.28))][(int)player->pos_x] != 'c')
			player->pos_y -= player->dir_y * player->move_speed;
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_x * (player->move_speed + 0.28))] != '1'
			&& data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_x * (player->move_speed + 0.28))] != 'c')
			player->pos_x -= player->dir_x * player->move_speed;
	}
	if (player->strafe_dir == -1)
	{
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_y * (player->move_speed + 0.28))] != '1'
			&& data->map.map[(int)player->pos_y][(int)(player->pos_x + player->dir_y * (player->move_speed + 0.28))] != 'c')
			player->pos_x += player->dir_y * player->move_speed;
		if (data->map.map[(int)(player->pos_y - player->dir_x * (player->move_speed + 0.28))][(int)player->pos_x] != '1'
			&& data->map.map[(int)(player->pos_y - player->dir_x * (player->move_speed + 0.28))][(int)player->pos_x] != 'c')
			player->pos_y -= player->dir_x * player->move_speed;
	}
	if (player->strafe_dir == 1)
	{
		if (data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_y * (player->move_speed + 0.28))] != '1'
			&& data->map.map[(int)player->pos_y][(int)(player->pos_x - player->dir_y * (player->move_speed + 0.28))] != 'c')
			player->pos_x -= player->dir_y * player->move_speed;
		if (data->map.map[(int)(player->pos_y + player->dir_x * (player->move_speed + 0.28))][(int)player->pos_x] != '1'
			&& data->map.map[(int)(player->pos_y + player->dir_x * (player->move_speed + 0.28))][(int)player->pos_x] != 'c')
			player->pos_y += player->dir_x * player->move_speed;
	}
}

void	rotate_player(t_player *play)
{
	double old_dir_x;
	double old_plane_x;
	double rot_v;

	rot_v = play->rot_speed;
	old_dir_x = play->dir_x;
	old_plane_x = play->plane_x;
	if (play->turn_dir == 1)
	{
		play->dir_x = play->dir_x * cos(-rot_v) - play->dir_y * sin(-rot_v);
		play->dir_y = old_dir_x * sin(-rot_v) + play->dir_y * cos(-rot_v);
		play->plane_x = play->plane_x * cos(-rot_v) - play->plane_y * sin(-rot_v);
		play->plane_y = old_plane_x * sin(-rot_v) + play->plane_y * cos(-rot_v);
	}
	if (play->turn_dir == -1)
	{
		play->dir_x = play->dir_x * cos(rot_v) - play->dir_y * sin(rot_v);
		play->dir_y = old_dir_x * sin(rot_v) + play->dir_y * cos(rot_v);
		play->plane_x = play->plane_x * cos(rot_v) - play->plane_y * sin(rot_v);
		play->plane_y = old_plane_x * sin(rot_v) + play->plane_y * cos(rot_v);
	}
}

void	rotate_player_mouse(t_player *play, double x)
{
	double	rot_v;
	double	old_dir_x;
	double	old_plane_x;

	rot_v = play->rot_speed * x * 0.05;
	old_plane_x = play->plane_x;
	old_dir_x = play->dir_x;
	play->dir_x = play->dir_x * cos(rot_v) - play->dir_y * sin(rot_v);
	play->dir_y = old_dir_x * sin(rot_v) + play->dir_y * cos(rot_v);
	play->plane_x = play->plane_x * cos(rot_v) - play->plane_y * sin(rot_v);
	play->plane_y = old_plane_x * sin(rot_v) + play->plane_y * cos(rot_v);
}

int	game_loop(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (data->player.walk_dir || data->player.strafe_dir)
		move_player(data, &data->player);
	if (data->player.turn_dir)
		rotate_player(&data->player);
	if (data->move_mouse)
	{
		mlx_mouse_get_pos(data->mlx.mlx, data->mlx.win, &x, &y);
		rotate_player_mouse(&data->player, (x - data->res_x / 2));
		if (x > data->res_x / 2 + 1 || x < data->res_x / 2 - 1
			|| y > data->res_y / 2 + 1 || y < data->res_y / 2 - 1)
			mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->res_x / 2,
				data->res_y / 2);
	}
	raycasting(data);
	if (!data->show_map)
		draw_minimap(data, (int)data->player.pos_x, (int)data->player.pos_y);
	else
		big_map(data);
	mlx_put_image_to_window(data->mlx.mlx,
		data->mlx.win, data->mlx.img.img, 0, 0);
	return (0);
}
