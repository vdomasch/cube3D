/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:33 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/03 11:21:45 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int keypress(int keysym, void *mlx)
{
	if (keysym == XK_Escape)
		mlx_loop_end(mlx);
	return (0);
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
	int		x;
	int		y;
	x = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "Put pixel!");
	
	img.img = mlx_xpm_file_to_image(mlx, "../assets/Tile_10_64x64.xpm", &img.width, &img.height);
	if (!img.img)
		printf("Error\n");
	printf("here\n");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	while (x < 64)
	{
		y = 0;
		while (y < 64)
		{
			printf("%d-%d: %X ", x, y, mlx_read_pixel(&img, x, y));
			y++;
		}
		printf("\n");
		x++;
	}
	mlx_hook(win, 2, 1L << 0, keypress, mlx);
	//mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
