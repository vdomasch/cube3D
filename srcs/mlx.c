/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:11:44 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/29 14:53:56 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}

void	clean_mlx(t_data *data)
{
	if (data->mlx)
	{
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	map_gen(t_data *data, void *mlx, void *win)
{
	(void)data;
	(void)mlx;
	(void)win;
	return (0);
}

int	mlx_settings(t_data *data)
{
	void	*mlx;
	void	*win;

	(void)data;
	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 1920, 1080, "Cub3D");
	if (!win)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (2);
	}
	/*
		  _				 ________	 _______	 _____	_____	_________									 _____		 _	 _____	_________
	     / \	|		|			|		|	|	  |	  |			|		|		|	|\     /|			|	  |	    / \	|	  |		|
		/  \	|		|			|		|	|_____|	  |			|		|		|	| \   / |			|	  |	   /  \	|_____|		|
	   /___\	|		|	____	|		|	|\	  	  |			|		|_______|	|  \-/  |			|_____|	  /__ \	|\	  		|
	  /    \	|		|		|	|		|	| \		  |			|		|		|	|		|			|		 /    \	| \			|
	 /     \	|		|		|	|		|	|  \	  |			|		|		|	|		|			|		/     \	|  \		|
	/      \	|______ |_______|	|_______|	|   \	__|__		|		|		|	|		|			|	   /      \	|   \		|


	if (!map_gen(data, mlx, win))
	{
		mlx_hook(win, 17, 1L << 3, mlx_loop_end, mlx);
		mlx_hook(win, 2, 1L << 0, key_press, data);
		mlx_loop(mlx);
	}
	*/
	clean_mlx(data);
	return (0);
}
