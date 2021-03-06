/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: litsmail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 20:11:12 by litsmail          #+#    #+#             */
/*   Updated: 2021/10/02 23:33:57 by litsmail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	draw_vert(t_img *image, t_point p0, t_point p1)
{
	int	ex;
	int	ey;
	int	delta_x;
	int	delta_y;
	int	i;

	ex = fabs(p1.x - p0.x);
	ey = fabs(p1.y - p0.y);
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
			p0.y ++;
			ex += delta_x * 2;
		}
	}
}

void	draw_horz(t_img *image, t_point p0, t_point p1)
{
	int	ex;
	int	ey;
	int	delta_x;
	int	delta_y;
	int	i;

	ex = fabs(p1.x - p0.x);
	ey = fabs(p1.y - p0.y);
	delta_x = ex;
	delta_y = ey;
	i = 0;
	while (i <= delta_y)
	{
		put_pixels(image, p0.x, p0.y);
		i++;
		p0.y ++;
		ey -= delta_x * 2;
		if (ey < 0)
		{
			p0.x ++;
			ey += delta_y * 2;
		}
	}
}

void	bressan_draw(t_img *image, t_point p0, t_point p1)
{
	int	ex;
	int	ey;
	int	delta_x;
	int	delta_y;

	ex = fabs(p1.x - p0.x);
	ey = fabs(p1.y - p0.y);
	delta_x = ex;
	delta_y = ey;
	if (p0.x > p1.x)
		return (bressan_draw(image, p1, p0));
	if (p0.y > p1.y)
		return (bressan_drawup(image, p0, p1));
	if (delta_x > delta_y)
		draw_vert(image, p0, p1);
	if (delta_x <= delta_y)
		draw_horz(image, p0, p1);
}
