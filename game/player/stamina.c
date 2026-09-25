/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stamina.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirloup <amirloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:46:25 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/07/25 16:50:13 by amirloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	stam_handling(t_cub *cub)
{
	cub->speed = 2;
	cub->sprint = true;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT_SHIFT) && cub->sprint == true)
	{
		cub->speed = 3;
		cub->stamina -= 2;
		if (cub->stamina < 2)
			cub->sprint = false;
	}
	else
		cub->sprint = false;
}

void	put_stamina(t_cub *cub)
{
	int	x;
	int	y;
	int	left;
	int	full;

	left = cub->width / 30;
	full = left + cub->stamina * cub->width / 500;
	x = left;
	while (x < left + cub->width / 5)
	{
		y = cub->height / 15;
		while (y < cub->height / 15 + cub->height / 50)
		{
			if (x < full)
				mlx_put_pixel(cub->world.hud, x, y, H_YELLOW);
			else
				mlx_put_pixel(cub->world.hud, x, y, H_YELLOW2);
			y++;
		}
		x++;
	}
}
