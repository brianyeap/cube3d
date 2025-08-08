/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:43:47 by brian             #+#    #+#             */
/*   Updated: 2025/08/08 23:55:59 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

t_type	*ft_getmap_config(char *file)
{
	int		ret;
	int		fd;
	char	*line;
	t_type	*map;

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
		ft_check_struct(map);
		free(line);
		close(fd);
		return (map);
	}
	else
		return (NULL);
}

void	ft_getmap_values(char *line, t_type *map)
{
	int	res;

	res = ft_strncmp(line, "R ", 2);
	if (!res)
		ft_set_resolution(line + 2, map->res, map);
	else if (!(ft_strncmp(line, "NO ", 3)))
		parse_texture_path(line + 3, &map->no, map);
	else if (!(ft_strncmp(line, "SO ", 3)))
		parse_texture_path(line + 3, &map->so, map);
	else if (!(ft_strncmp(line, "WE ", 3)))
		parse_texture_path(line + 3, &map->we, map);
	else if (!(ft_strncmp(line, "EA ", 3)))
		parse_texture_path(line + 3, &map->ea, map);
	else if (!(ft_strncmp(line, "S ", 2)))
		parse_texture_path(line + 2, &map->s, map);
	else if (!(ft_strncmp(line, "F ", 2)))
		parse_texture_path(line + 2, &map->f, map);
	else if (!(ft_strncmp(line, "C ", 2)))
		parse_texture_path(line + 2, &map->c, map);
	else if (line[0] != '\0')
		ft_exit("Unkown identifier(s) in file\n", map);
}

void	ft_set_resolution(char *str, int *target, t_type *map)
{
	int		i;
	char	**splited;

	i = 0;
	if (ft_check_str(str, "0123456789 "))
		ft_exit("Not a valid resolution!\n", map);
	if (target[2] != 0)
		ft_exit("Resolution already set!\n", map);
	splited = ft_split(str, ' ');
	while (splited[i] != NULL)
		i++;
	if (i != 2)
		ft_exit("Resolution not gud :(\n", map);
	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited);
	target[0] = ft_atoi(str);
	str = ft_strchr(str, ' ');
	target[1] = ft_atoi(str);
	if (target[0] < 100)
		target[0] = 100;
	if (target[1] < 100)
		target[1] = 100;
	target[2] = 1;
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
