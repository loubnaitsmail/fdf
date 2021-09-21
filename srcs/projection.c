#include "fdf.h"

void	iso(int x, int y, int z)
{
    int	previous_x;
    int	previous_y;

    previous_x = x;
    previous_y = y;
    x = (previous_x - previous_y) * cos(0.523599);
    y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	change_to_iso(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->y_max)
	{
		j = 0;
		while (j < fdf->x_max)
		{	
			iso(i, j, fdf->original_map[i][j]);
			j++;
		}
		i++;
	}
}

 int	change_projection(t_fdf *fdf)
{
	if (fdf->projection == ISOMETRIC)
	{
		fdf->projection = PARALLELE;
	}
	else if (fdf->projection == PARALLELE)
	{
		fdf->projection = ISOMETRIC;
		change_to_iso(fdf);
		draw(fdf);
	}
	/*else
	{
		fdf->projection = PARALLELE;
	}*/
	return (1);
}

/*int	keys_action(int key, void *param)
{

	t_fdf	*fdf;
	t_mlx	*mlx;

	fdf = (t_fdf *)param;
	mlx = fdf->mlx;
	printf("key %d\n",key);
	if (key == CHANGE_PROJECTION)
		change_projection(fdf);
	return (1);
}*/
