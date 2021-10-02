/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 19:47:25 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/02 22:43:35 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	iso(t_point *p)
{
	double	previous_x;
	double	previous_y;

	previous_x = p->x;
	previous_y = p->y;
	p->x = (previous_x - previous_y) * cos(0.523599);
	p->y = - p->z + (previous_x + previous_y) * sin(0.523599);
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
			iso(&(fdf->map[i][j]));
			j++;
		}
		i++;
	}
}

void	change_to_paral(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->y_max)
	{
		j = 0;
		while (j < fdf->x_max)
		{
			fdf->map[i][j].y = i;
			fdf->map[i][j].x = j;
			fdf->map[i][j].z = fdf->original_map[i][j];
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
		change_to_paral(fdf);
	}
	else if (fdf->projection == PARALLELE)
	{
		fdf->projection = ISOMETRIC;
		change_to_iso(fdf);
	}
	return (1);
}
