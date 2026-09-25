/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:34:32 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/12 09:32:13 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	calculation_for_the_fog(t_cub *cub, int x, int y, int *opacity)
{
	int	calc_x;
	int	calc_y;

	if (x % 4 == 0 || y % 4 == 0)
	{
		if (x >= cub->width / 2)
		{
			calc_x = x - cub->width / 2;
		}
		else
			calc_x = cub->width / 2 - x;
		if (y > cub->height / 2)
			calc_y = y - cub->height / 2;
		else
			calc_y = cub->height / 2 - y;
		*opacity = sqrt(calc_x * calc_x + calc_y * calc_y);
		*opacity = *opacity * 1000 / cub->width;
	}
	if (*opacity > 240)
		*opacity = 240;
	if (*opacity < 0)
		*opacity = 0;
	return (*opacity);
}

void	fog(t_cub *cub)
{
	int	x;
	int	y;
	int	opacity;

	x = 0;
	y = 0;
	opacity = 255;
	while (y < cub->height)
	{
		x = 0;
		while (x < cub->width)
		{
			calculation_for_the_fog(cub, x, y, &opacity);
			mlx_put_pixel(cub->world.fog, x, y, opacity);
			x++;
		}
		y++;
	}
}
