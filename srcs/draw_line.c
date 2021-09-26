#include "fdf.h"

void	put_pixels(t_img *image, int x, int y)
{
	if (y >= 0 && x >= 0 && y < image->height && x < image->width)
		image->addr_img[y * image->width + x] = 0x00ff00ff;
}

void	draw_vertical_lines(t_img *image, t_point p0, t_point p1)
{

	int		x0;
	int		x1;
	int		y0;
	int		y1;

	x0 = p0.x;
	x1 = p1.x;
	y0 = p0.y;
	y1 = p1.y;
	while (y0 != y1)
	{
		put_pixels(image, x0, y0);
		if (y0 < y1)
			y0++;
		else
			y0--;
	}
}

/*void	draw_horiz_lines(t_img *image, t_point p0, t_point p1, int diff_y)
{
	int		dx;
	int		dy;
	int		erreur;
	
	erreur = (p1.x - p0.x) * diff_y;
	dx = (p1.x - p0.x) * 2;
	dy = (p1.y - p0.y) * 2;
	put_pixels(image, p0.x, p0.y);
	erreur -= (dy *diff_y);
	while (erreur <= 0)
	{
		p0.y += diff_y;
		erreur += dx;
		put_pixels(image, p0.x, p0.y);
	}
	p0.x += 1;
}*/

/*void	bressan_draw(t_img *image, t_point p0, t_point p1, int diff_y)
{
	int		dx;
	int		dy;
	int		erreur;

	if (p0.x > p1.x)
	{
		bressan_draw(image, p1, p0, diff_y *-1);
		return ;
	}
	dx = (p1.x - p0.x) * 2;
	dy = (p1.y - p0.y) * 2;
	erreur = (p1.x - p0.x) * diff_y;
	//draw_horiz_lines(image, p0, p1, diff_y);
	while (p0.x < p1.x)
	{
		put_pixels(image, p0.x, p0.y);
		erreur -= (dy *diff_y);
		while (erreur <= 0)
		{
			p0.y += diff_y;
			erreur += dx;
			put_pixels(image, p0.x, p0.y);
		}
		p0.x += 1;
	}
	draw_vertical_lines(image, p0, p1);
}*/

void	my_bressan_draw(t_img *image, int x1, int y1, int x2, int y2)
{
	int ex = abs(x2-x1);
	int	ey = abs(y2-y1);
	int dx = 2*ex;
	int dy = 2*ey;
	int Dx = ex;
	int Dy = ey;
	int i = 0;
	int Xincr = 1;
	int Yincr = 1;

	if (x1>x2)
		Xincr = -1;
	if (y1>y2)
		Yincr = -1;
	//1cas
	printf("Dx = %d et Dy = %d\n", Dx, Dy);
	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			put_pixels(image, x1, y1);
			i++;
			x1 += Xincr;
			ex -= dy;
			if (ex < 0)
			{
				y1 += Yincr;
				ex += dx;
			}
		}
	}
	//2cas
	if (Dx < Dy)
	{
		while (i <= Dy)
		{
			put_pixels(image, x1, y1);
			i++;
			y1 += Yincr;
			ey -= dx;
			if (ey < 0)
			{
				x1 += Yincr;
				ey += dy;
			}
		}
	}
	if (Dy == Dx)
		printf("Cas Dy == Dx\n");
	if (Dy == 0)
		printf("Cas Dy = 0\n");
	if (Dx == 0)
		printf("Cas Dx = 0\n");
	

	//cas Dy = 0 
	//cas Dx = 0
}

void	p_link(t_fdf *fdf, t_point p0, t_point p1)
{
	int			diff_y;

	p0.x = (p0.x - fdf->x_origin) * fdf->zoom;
	p0.y = (p0.y - fdf->y_origin) * fdf->zoom;
	p1.x = (p1.x - fdf->x_origin) * fdf->zoom;
	p1.y = (p1.y - fdf->y_origin) * fdf->zoom;

	diff_y = 1;
	if (p0.y > p1.y)
		diff_y = -1;
	//bressan_draw(fdf->mlx->img_mlx, p0, p1, diff_y);
	my_bressan_draw(fdf->mlx->img_mlx, p0.x, p0.y, p1.x, p1.y);
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

/*void information(t_fdf *fdf)
{
	printf("x_max = %d\n", fdf->x_max);
	printf("y_max = %d\n", fdf->y_max);
	int x = 0;
	int y = 0;
	while(y < fdf->y_max)
	{
		 x = 0;
		while (x < fdf->x_max)
		{
			printf("%2d ", fdf->original_map[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
	printf("imqge heigh = %d\n", fdf->mlx->img_mlx->height);
	printf("imqge widht = %d\n", fdf->mlx->img_mlx->width);
	printf("imqge line_lenght = %d\n", fdf->mlx->img_mlx->line_length);
	printf("imqge endian = %d\n", fdf->mlx->img_mlx->endian);
	printf("imqge bitpixel  = %d\n", fdf->mlx->img_mlx->bits_per_pixels);

}*/

void	draw(t_fdf *fdf)
{
	t_mlx	*mlx;

	mlx = fdf->mlx;
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
	draw_points(fdf, mlx->img_mlx);
	//information(fdf);
	link_points(fdf);
	//bressan_draw(mlx->img_mlx, 0, 0, 42, 42, 1);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_mlx->img_ptr, 0, 0);
}
