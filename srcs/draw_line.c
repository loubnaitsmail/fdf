#include "fdf.h"

void	put_pixels(t_img *image, int x, int y)
{
	if (y >= 0 && x >= 0 && y < image->height && x < image->width)
		image->addr_img[y * image->width + x] = 0x0000ff00;
}

void	my_bressan_draw(t_img *image, t_point p0, t_point p1, int Xincr, int Yincr)
{
	int ex = fabs(p1.x - p0.x);
	int	ey = fabs(p1.y - p0.y);
	int dx = 2*ex;
	int dy = 2*ey;
	int Dx = ex;
	int Dy = ey;
	int i = 0;

	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			put_pixels(image, p0.x, p0.y);
			i++;
			p0.x += Xincr;
			ex -= dy;
			if (ex < 0)
			{
				p0.y += Yincr;
				ex += dx;
			}
		}
	}
	//2cas
	if (Dx <= Dy)
	{
		while (i <= Dy)
		{
			put_pixels(image, p0.x, p0.y);
			i++;
			p0.y += Yincr;
			ey -= dx;
			if (ey < 0)
			{
				p0.x += Xincr;
				ey += dy;
			}
		}
	}
}

void	p_link(t_fdf *fdf, t_point p0, t_point p1)
{
	int		Xincr;
	int		Yincr;

	Xincr = 1;
	Yincr = 1;
	if (p0.x > p1.x)
		Xincr = -1;
	if (p0.y > p1.y)
		Yincr = -1;
	p0.x = (p0.x - fdf->x_origin) * fdf->zoom;
	p0.y = (p0.y - fdf->y_origin) * fdf->zoom;
	p1.x = (p1.x - fdf->x_origin) * fdf->zoom;
	p1.y = (p1.y - fdf->y_origin) * fdf->zoom;
	my_bressan_draw(fdf->mlx->img_mlx, p0, p1, Xincr, Yincr);
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
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_mlx->img_ptr, 0, 0);
}
