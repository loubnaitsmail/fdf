/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:38:22 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/02 23:19:38 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	draw_vertup(t_img *image, t_point p0, t_point p1)
{
	int	ex;
	int	ey;
	int	delta_x;
	int	delta_y;
	int	i;

	ex = ft_abs(p1.x - p0.x);
	ey = ft_abs(p1.y - p0.y);
	delta_x = ex;
	delta_y = ey;
	i = 0;
	while (i <= delta_x)
	{
		put_pixels(image, p0.x, p0.y);
		i++;
		p0.x ++;
		ex -= delta_y * 2;
		if (ex < 0)
		{
			p0.y --;
			ex += delta_x * 2;
		}
	}
}

void	draw_horzup(t_img *image, t_point p0, t_point p1)
{
	int	ex;
	int	ey;
	int	delta_x;
	int	delta_y;
	int	i;

	ex = ft_abs(p1.x - p0.x);
	ey = ft_abs(p1.y - p0.y);
	delta_x = ex;
	delta_y = ey;
	i = 0;
	while (i <= delta_y)
	{
		put_pixels(image, p0.x, p0.y);
		i++;
		p0.y --;
		ey -= delta_x * 2;
		if (ey < 0)
		{
			p0.x ++;
			ey += delta_y * 2;
		}
	}
}

void	bressan_drawup(t_img *image, t_point p0, t_point p1)
{
	int	ex;
	int	ey;
	int	delta_x;
	int	delta_y;

	ex = ft_abs(p1.x - p0.x);
	ey = ft_abs(p1.y - p0.y);
	delta_x = ex;
	delta_y = ey;
	if (delta_x > delta_y)
		draw_vertup(image, p0, p1);
	else
		draw_horzup(image, p0, p1);
}
