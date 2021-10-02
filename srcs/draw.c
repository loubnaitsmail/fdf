/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:17:29 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/02 22:10:23 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	put_pixels(t_img *image, int x, int y)
{
	if (y >= 0 && x >= 0 && y < image->height && x < image->width)
		image->addr_img[y * image->width + x] = 0x0000ff00;
}

void	p_link(t_fdf *fdf, t_point p0, t_point p1)
{
	p0.x = (p0.x - fdf->x_origin) * fdf->zoom;
	p0.y = (p0.y - fdf->y_origin) * fdf->zoom;
	p1.x = (p1.x - fdf->x_origin) * fdf->zoom;
	p1.y = (p1.y - fdf->y_origin) * fdf->zoom;
	bressan_draw(fdf->mlx->img_mlx, p0, p1);
}

void	link_points(t_fdf *fdf)
{
	int			i;
	int			j;

	j = 0;
	while (j < fdf->y_max)
	{
		i = 0;
		while (i < fdf->x_max)
		{
			if (i > 0)
				p_link(fdf, fdf->map[j][i - 1], fdf->map[j][i]);
			if (j > 0)
				p_link(fdf, fdf->map[j - 1][i], fdf->map[j][i]);
			i++;
		}
		j++;
	}
}

void	draw_points(t_fdf *fdf, t_img *image)
{
	int			i;
	int			j;
	t_point		p;

	ft_bzero(image->addr_img, image->line_length * image->height);
	i = 0;
	while (i < fdf->y_max)
	{
		 j = 0;
		while (j < fdf->x_max)
		{
			p.x = (fdf->map[i][j].x - fdf->x_origin) * fdf->zoom;
			p.y = (fdf->map[i][j].y - fdf->y_origin) * fdf->zoom;
			put_pixels(image, p.x, p.y);
			j++;
		}
		i++;
	}
}

void	draw(t_fdf *fdf)
{
	t_mlx	*mlx;

	mlx = fdf->mlx;
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
	draw_points(fdf, mlx->img_mlx);
	link_points(fdf);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img_mlx->img_ptr, 0, 0);
}
