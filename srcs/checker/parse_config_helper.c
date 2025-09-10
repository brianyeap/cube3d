/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:17:22 by brian             #+#    #+#             */
/*   Updated: 2025/09/10 16:19:34 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_is_cub_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strcmp(filename + (len - 4), ".cub") == 0);
}

void	ck_struct_and_close_fd(t_type *map, int fd, char *line)
{
	ft_check_struct(map);
	free(line);
	close(fd);
}

