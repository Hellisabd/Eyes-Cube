/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrosjea <bgrosjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:25:16 by bgrosjea          #+#    #+#             */
/*   Updated: 2024/08/01 11:06:47 by bgrosjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	refresh(t_cub *cub)
{
	cub->player.dir_up = cub->rot;
	cub->player.dir_down = cub->rot + PI;
	if (cub->player.dir_down >= 2 * PI)
		cub->player.dir_down -= 2 * PI;
	cub->player.dir_left = cub->rot + 3 * PI / 2;
	if (cub->player.dir_left >= 2 * PI)
		cub->player.dir_left -= 2 * PI;
	cub->player.dir_right = cub->rot + PI / 2;
	if (cub->player.dir_right >= 2 * PI)
		cub->player.dir_right -= 2 * PI;
	raycasting(cub);
	if (cub->stamina < 100 && cub->anim.frame % 2 == 0)
		cub->stamina++;
	put_stamina(cub);
	cub->anim.frame++;
	blink(cub);
	anim_enemy(cub);
	check_doors(cub);
	draw_ray(&cub->ray, &cub->mini_map, cub, H_RED);
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	cub->anim.time += cub->mlx->delta_time;
	if (cub->anim.time > 0.03)
	{
		if (cub->alive == true)
			move(cub);
		refresh(cub);
		if (cub->alive == true && cub->n_enemy == 1)
		{
			move_enemy(cub);
			check_death(cub);
		}
		if (cub->alive == true && cub->n_exit == 1)
			check_exit(cub);
		cub->anim.time = 0;
	}
}

void	ft_cursor(t_cub *cub)
{
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_DISABLED);
	cub->status = 1;
}

void	init_pos_count(t_cub *cub)
{
	cub->n_enemy = count_c(cub->map, 'A');
	cub->n_exit = count_c(cub->map, 'X');
	if (cub->n_enemy > 1)
		exit((print_error("Too many enemies!\n"), \
			free_map_stuff(cub->map), EXIT_FAILURE));
	if (cub->n_exit > 1)
		exit((print_error("Too many exits!\n"), \
			free_map_stuff(cub->map), EXIT_FAILURE));
}

void	open_window(t_cub *cub)
{
	cub->stamina = 100;
	init_pos_count(cub);
	init_mlx_window(cub);
	init_data_mini_map(&cub->mini_map, cub->map, cub->height);
	set_player_pos(cub);
	set_enemy_pos(cub);
	set_exit_pos(cub);
	ft_cursor(cub);
	init_raycast(cub);
	lets_go_3d(cub);
	init_anim(cub);
	raycasting(cub);
	map_to_window(cub, false);
	draw_ray(&cub->ray, &cub->mini_map, cub, H_RED);
	mlx_set_mouse_pos(cub->mlx, cub->width / 2, cub->height / 2);
	fog(cub);
	mlx_key_hook(cub->mlx, interaction, cub);
	mlx_loop_hook(cub->mlx, ft_hook, (void *)cub);
	mlx_cursor_hook(cub->mlx, rotations, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}
