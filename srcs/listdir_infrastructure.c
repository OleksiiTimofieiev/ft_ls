/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdir_infrastructure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timofieiev <timofieiev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 11:07:42 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/11 19:20:23 by timofieiev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_dump_cleaner(t_temp **list, char **path2, DIR **dir)
{
	delete_list(list);
	closedir(*dir);
	free(*path2);
}

void	init_path2(char **path2, char *name)
{
	size_t	len;
	char	*tmp;

	*path2 = ft_strdup(name);
	len = ft_strlen(*path2);
	if ((*path2)[len - 1] != '/')
	{
		tmp = ft_strdup(*path2);
		free(*path2);
		*path2 = ft_strjoin(tmp, "/");
		free(tmp);
	}
}

void	str_copy(char *dst, char *src)
{
	int i;

	i = 0;
	while (i < 20)
	{
		dst[i] = src[i];
		i++;
	}
	dst[19] = '\0';
}
