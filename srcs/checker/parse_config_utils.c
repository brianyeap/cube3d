/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:43:47 by brian             #+#    #+#             */
/*   Updated: 2025/09/15 16:06:15 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_check_struct(t_type *map)
{
	if (!map->no || !map->so || !map->we || !map->ea)
		ft_exit("Missing texture identifier(s): need NO, SO, WE, EA\n", map);
	if (map->f_rgb < 0 || map->c_rgb < 0)
		ft_exit("Floor or ceiling color missing\n", map);
	if (map->no[0] == 0)
		ft_exit("North texture missing\n", map);
	if (map->so[0] == 0)
		ft_exit("South texture missing\n", map);
	if (map->ea[0] == 0)
		ft_exit("East texture missing\n", map);
	if (map->we[0] == 0)
		ft_exit("West texture missing\n", map);
}

void	ft_init_t_type(t_type *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->c_rgb = -1;
	map->f_rgb = -1;
	map->height = 0;
	map->width = 0;
	map->res[0] = WIN_W;
	map->res[1] = WIN_H;
}

int	ft_strmultichr(char *str, char *chrlst)
{
	int		i;
	int		flaged;
	char	*ptr;

	i = 0;
	ptr = NULL;
	flaged = 1;
	if ((ft_strlen(str) == 0) || ((str == NULL) && (chrlst == NULL)))
		return (0);
	while (str[i])
	{
		ptr = ft_strchr(chrlst, str[i]);
		if (!ptr)
			flaged = 0;
		i++;
	}
	return (flaged);
}

int	check_ending(char *str, char *end)
{
	int	len;
	int	count;

	len = ft_strlen(str) - 1;
	count = ft_strlen(end) - 1;
	if (len == count)
		return (0);
	while ((str[len--] == end[count]) && ((count > 0) && (len > 0)))
		count--;
	if (count == 0)
		return (1);
	else
		return (0);
}

void	ft_exit(char *str, t_type *map)
{
	ft_putstr(RED"Error\n");
	ft_putstr(str);
	ft_putstr(RST"\n");
	free(map);
	exit(0);
}
