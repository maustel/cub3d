/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:38:12 by maustel           #+#    #+#             */
/*   Updated: 2024/12/18 16:38:12 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_cub cub;
	if (argc != 2)
		return (print_error(E_ARGS));
	parser(argv[1], &cub);
	(void)argv;
	return (0);
}
