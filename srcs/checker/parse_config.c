/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:43:47 by brian             #+#    #+#             */
/*   Updated: 2025/09/10 16:27:06 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_type	*ft_getmap_config(char *file)
{
	int		ret;
	int		fd;
	char	*line;
	t_type	*map;

	if (!ft_is_cub_extension(file))
		exit_cube(NULL, "\n\nError\nPlease provide a \'.cub\' file\n", 0);
	map = malloc(sizeof(t_type));
	fd = open(file, O_RDONLY);
	if (fd > 0)
	{
		map->res[0] = 0;
		ft_init_t_type(map);
		ret = get_next_line(fd, &line);
		while (ret && ((ft_strmultichr(line, " 012SNEW")) != 1))
		{
			ft_getmap_values(line, map);
			free(line);
			ret = get_next_line(fd, &line);
		}
		ck_struct_and_close_fd(map, fd, line);
		return (map);
	}
	else
		return (NULL);
}

void	ft_getmap_values(char *line, t_type *map)
{
	map->res[0] = WIN_W;
	map->res[1] = WIN_H;
	if (!(ft_strncmp(line, "NO ", 3)))
		parse_texture_path(line + 3, &map->no, map);
	else if (!(ft_strncmp(line, "SO ", 3)))
		parse_texture_path(line + 3, &map->so, map);
	else if (!(ft_strncmp(line, "WE ", 3)))
		parse_texture_path(line + 3, &map->we, map);
	else if (!(ft_strncmp(line, "EA ", 3)))
		parse_texture_path(line + 3, &map->ea, map);
	else if (!(ft_strncmp(line, "F ", 2)))
		parse_color_rgb(line + 2, &map->f_rgb, map);
	else if (!(ft_strncmp(line, "C ", 2)))
		parse_color_rgb(line + 2, &map->c_rgb, map);
	else if (line[0] != '\0')
		ft_exit("Unkown identifier(s) in file\n", map);
}

void	parse_color_rgb(char *str, int *target, t_type *map)
{
	char	**split;
	int		i;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		ft_exit("Invalid RGB format\n", map);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_exit("RGB values must be 0–255\n", map);
	*target = (r << 16) | (g << 8) | b;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	parse_texture_path(char *str, char **target, t_type *map)
{
	int	fd;

	if (check_ending(str, ".xpm"))
	{
		if (*target != NULL)
			ft_exit("Texture already set!\n", map);
		fd = open(str, O_RDONLY);
		if (fd == -1)
			ft_exit("Invalid path for one of the textures\n", map);
		*target = ft_strdup(str);
		close(fd);
	}
	else
		ft_exit("Please provide a \'.xpm\' file\n", map);
}

char	*ft_check_str(char *str, char *chrs)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		while (chrs[i])
		{
			if (*str == chrs[i])
				flag = 1;
			i++;
		}
		if (flag == 0)
			return (str);
		flag = 0;
		i = 0;
		str++;
	}
	return (NULL);
}
