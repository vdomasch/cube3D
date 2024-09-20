/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:33 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/03 11:36:11 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int keypress(int keysym, void *mlx)
{
	if (keysym == XK_Escape)
		mlx_loop_end(mlx);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	mlx_read_pixel(t_data *data, int x, int y)
{
	char	*dst;
	unsigned int	color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

int main(void)
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_data	tile10;
	int		x;
	int		y;
	x = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "Put pixel!");
	
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	tile10.img = mlx_xpm_file_to_image(mlx, "../../assets/Tile_10_64x64.xpm", &img.width, &img.height);
	tile10.addr = mlx_get_data_addr(tile10.img, &tile10.bits_per_pixel, &tile10.line_length, &tile10.endian);

	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			if (y < 400)
				my_mlx_pixel_put(&img, x, y, 0x0000FFFF);
			else if (y < 464)
				my_mlx_pixel_put(&img, x, y, mlx_read_pixel(&tile10, x % 64, y % 64));
			else
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
			y++;
		}
		x++;
	}
	mlx_hook(win, 2, 1L << 0, keypress, mlx);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
