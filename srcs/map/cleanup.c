/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:28:21 by brian             #+#    #+#             */
/*   Updated: 2025/08/06 18:45:23 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	cleanUp(t_brain *b)
{
	if (b)
	{
		free(b);
	}
}

void	exit_cube(t_brain *brain, char *msg, int exit_now)
{
	static t_brain *b = NULL;

	if (b == NULL && brain != NULL)
	{
		b = brain;
		ft_putstr("Stored brain pointer\n");
	}
	if (exit_now)
		return ;
	ft_putstr("\nCub3D Exit - Error: ");
	ft_putstr(msg);
	cleanUp(b);
	ft_putstr("Clean Up OK\n");
	ft_putstr("Exit Done\n");
	exit(0);
}
