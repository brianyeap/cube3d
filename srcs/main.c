/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:46:56 by brian             #+#    #+#             */
/*   Updated: 2025/08/06 18:59:54 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int argc, char **argv)
{
	(void) argv;
	if (argc < 2 || argc > 3)
		exit_cube(NULL, "Invalid number of arguments\n", 0);
	return (0);
}
