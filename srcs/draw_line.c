#include "fdf.h"

void	put_pixels(t_img *image, int x, int y)
{
	if (y >= 0 && x >= 0 && y < image->height && x < image->width)
		image->addr_img[y * image->width + x] = 0x00ff00ff;
}

void	bressan_draw(t_img *image, int x0, int y0, int x1, int y1, int diff_y)
{
	int		dx;
	int		dy;
	int		erreur;

	if (x0 > x1)
	{
		bressan_draw(image, x1, y1, x0, y0, diff_y *-1);
		return ;
	}

	dx = (x1 - x0) * 2;
	dy = (y1 - y0) * 2;
	erreur = (x1 - x0) * diff_y;
	while (x0 < x1)
	{
		put_pixels(image, x0, y0);
		erreur -= (dy *diff_y);
		while (erreur <= 0)
		{
			y0 += diff_y;
			erreur += dx;
			put_pixels(image, x0, y0);
			//printf("1- je put pixel\n");
		}
		x0 += 1;
		while (y0 != y1)
		{
			put_pixels(image, x0, y0);
			//printf("2- je put pixel\n");
			if (y0 < y1)
				y0++;
			else
				y0--;
		}

	}
	while (y0 != y1)
	{
		y0 += diff_y;
		put_pixels(image, x0, y0);

	}
}

void	link_points(t_fdf *fdf)
{
	int			x;
	int			y;
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			diff_y;	

	y = 0;
	diff_y = 1;
	while (y < fdf->y_max)
	{
		x = 0;
		while (x < fdf->x_max)
		{
			x0 = (fdf->map[y][x].x - fdf->x_origin) * fdf->zoom;
			y0 = (fdf->map[y][x].y - fdf->y_origin) * fdf->zoom;
			//printf("x0 = %d et y0 = %d\n", x0, y0);
			if (x > 0)
			{
				x1 = (fdf->map[y][x - 1].x - fdf->x_origin) * fdf->zoom;
				y1 = (fdf->map[y][x - 1].y - fdf->y_origin) * fdf->zoom;;
				//printf(" x1 = %d et y1 = %d\n",x1,y1);
				if (y0 > y1)
					diff_y = -1;
				bressan_draw(fdf->mlx->img_mlx, x0, y0, x1, y1, diff_y); //la mm chose
			}
			if (y > 0)
			{
				x1 = (fdf->map[y - 1][x].x - fdf->x_origin) * fdf->zoom;
				y1 = (fdf->map[y - 1][x].y - fdf->y_origin) * fdf->zoom;
				//printf("if y > 0 ->  x1 = %d et y1 = %d\n", x1 ,y1);
				if (y0 > y1)
					diff_y =-1;
				bressan_draw(fdf->mlx->img_mlx, x0, y0, x1, y1, diff_y);
			}
			x++;
		}
		y++;
	}
}

void	draw_points(t_fdf *fdf, t_img *image)
{
	int			i;
	int			j;
	int			x;
	int			y;

	ft_bzero(image->addr_img, image->line_length * image->height);
	i = 0;
	while (i < fdf->y_max)
	{
		 j = 0;
		while (j < fdf->x_max)
		{
			//point = &(fdf->map[i][j]);
			//p.x = point->x * fdf->zoom;
			//p.y = point->y * fdf->zoom;
			x = (fdf->map[i][j].x - fdf->x_origin) * fdf->zoom;
			y = (fdf->map[i][j].y - fdf->y_origin) * fdf->zoom;
			//printf("hello\n");
			put_pixels(image, x, y);
			//put_pixels(image, (x - fdf->x_origin) * fdf->zoom, (y - fdf->y_origin) * fdf->zoom);
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
	bressan_draw(mlx->img_mlx, 0, 0, 42, 42, 1);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_mlx->img_ptr, 0, 0);

}
