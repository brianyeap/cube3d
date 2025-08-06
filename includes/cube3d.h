/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:22:12 by brian             #+#    #+#             */
/*   Updated: 2025/08/06 18:49:17 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <string.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct s_brain
{
	int			initialized;

}	t_brain;

// Cleanups
void	exit_cube(t_brain *brain, char *msg, int exit_now);

#endif