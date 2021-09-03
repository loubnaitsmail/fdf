#include "fdf.h"

void	bressan_draw(t_fdf *fdf, t_point p0, t_point p1)
{
	int		dx;
	int		dy;
	int		erreur;
	int		diff_y;

	diff_y = 1;
	if (p0.y > p1.y)
		diff_y =-1;

	dx = (p1.x - p0.x) * 2;
	dy = (p1.y - p0.x) * 2;
	erreur = (p1.x - p0.x) * diff_y;
	while (p0.x < p1.x)
	{
		mlx_pixel_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, p0.x, p0.y, 0xFFFFFF);
		erreur -= (dy *diff_y);
		while( erreur <= 0)
		{
			p0.y += diff_y;
			erreur += dx;
			mlx_pixel_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, p0.x, p0.y, 0xFFFFFF);
		}
		p0.x += 1
		while (;
	}



}

void	draw_points(t_fdf *fdf)
{
	//bzero ?
	int		i;
	int		j;
	t_point		*point;

	i = 0;
	while (i < fdf->y_max)
	{
		j = 1;
		while (j < fdf->map[i][0].x)
		{
			point = &(fdf->map[i][j]);
			//point->color
			//draw_contour()
			mlx_pixel_put(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr, i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	link_points(t_fdf *fdf)
{
	int			x;
	int			y;

	y = 0;
	while (y < fdf->y_max)
	{
		x = 1; //?
		while (x < fdf->map[y][0].x)
		{
			if (x > 1)
				bressan_draw(fdf, fdf->map[y - 1][x], fdf->map[y][x]);
			if (y > 0 && fdf->map[y - 1][0].x)
				bressan_draw(fdf, fdf->map[y - 1][x], fdf->map[y][x]);
			x++;
		}
		y++;
	}
}

void	draw(t_fdf *fdf)
{
	t_mlx	*mlx;
	mlx = fdf->mlx;
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
	draw_points(fdf);
	link_points(fdf);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_mlx->img_ptr, 0, 0);

}
