/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:32:28 by maustel           #+#    #+#             */
/*   Updated: 2025/01/10 10:32:28 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
	check if everything present (NO, WE, SO, EA, F, C , map)
*/
static void	check_all_there(t_cub *cub)
{
	if (!cub->assets->no)
		print_error_free_exit(E_MISSING, cub, "'NO' file path\n");
	if (!cub->assets->ea)
		print_error_free_exit(E_MISSING, cub, "'EA' file path\n");
	if (!cub->assets->so)
		print_error_free_exit(E_MISSING, cub, "'SO' file path\n");
	if (!cub->assets->we)
		print_error_free_exit(E_MISSING, cub, "'WE' file path\n");
	if (cub->assets->c > 16777215)
		print_error_free_exit(E_MISSING, cub, "'C' ceiling color\n");
	if (cub->assets->f >16777215)
		print_error_free_exit(E_MISSING, cub, "'F' floor color\n");
	// if (!cub->mapy->map)
	// 	print_error_free_exit(E_MISSING, cub, "map\n");
}

void	check_filename_valid(char *path, t_cub *cub)	//somewhere else
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 4] != '.' || path[i - 3] != 'c'
		|| path[i - 2] != 'u' || path[i - 1] != 'b')
			print_error_free_exit(E_FILENAME, cub, NULL);
}

static void	check_filepaths_valid(t_cub *cub)
{
	int		fd;

	fd = open(cub->assets->no, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, cub, cub->assets->no);
	if (close(fd) < 0)
		print_error_free_exit(errno, cub, cub->assets->no);
	fd = open(cub->assets->ea, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, cub, cub->assets->ea);
	if (close(fd) < 0)
		print_error_free_exit(errno, cub, cub->assets->ea);
	fd = open(cub->assets->so, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, cub, cub->assets->so);
	if (close(fd) < 0)
		print_error_free_exit(errno, cub, cub->assets->so);
	fd = open(cub->assets->we, O_RDONLY);
	if (fd < 0)
		print_error_free_exit(errno, cub, cub->assets->we);
	if (close(fd) < 0)
		print_error_free_exit(errno, cub, cub->assets->we);
}
//valid characters: 1, 0, N, E, S, W
void	check_map(char **map, t_cub *cub)
{
	if (!map || !*map)
		print_error_free_exit(E_NOMAP, cub, NULL);
}

void	check_content(t_cub *cub)
{
	check_all_there(cub);
	check_filepaths_valid(cub);
	check_map(cub->mapy->map, cub);	//todo

}