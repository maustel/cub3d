/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:31:01 by dhuss             #+#    #+#             */
/*   Updated: 2025/03/13 10:31:49 by dhuss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_pngs(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i])
		{
			mlx_delete_texture(game->texture[i]);
			game->texture[i] = NULL;
		}
		i++;
	}
}

void	free_mlx(t_game *game, t_custom_error err, int ex)
{
	free_pngs(game);
	if (game->wall_image)
	{
		mlx_delete_image(game->mlx, game->wall_image);
		game->wall_image = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	if (ex == 1)
		print_error_free_exit(err, game->cub, NULL);
	else if (ex == 2)
	{
		if (game->cub)
			free_cub(game->cub);
		exit(EXIT_SUCCESS);
	}
}
