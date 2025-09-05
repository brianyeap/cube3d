/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:28:21 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 17:49:11 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	clean_up(t_brain *b)
{
	if (b)
	{
		free(b);
	}
}

void	exit_cube(t_brain *brain, char *msg, int exit_now)
{
	static t_brain	*b;

	b = NULL;
	if (b == NULL && brain != NULL)
	{
		b = brain;
		ft_putstr("Stored brain pointer\n");
	}
	if (exit_now)
		return ;
	ft_putstr(RED"\nCub3D Exit - Error: ");
	ft_putstr(msg);
	ft_putstr(RST"\n");
	clean_up(b);
	ft_putstr(YELO"Clean Up OK\n"RST);
	ft_putstr(BLUE"Exit Done\n"RST);
	exit(0);
}
