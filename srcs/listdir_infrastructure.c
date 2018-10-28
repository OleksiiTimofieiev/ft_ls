/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdir_infrastructure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 11:07:42 by otimofie          #+#    #+#             */
/*   Updated: 2018/10/28 11:08:51 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

void	ft_dump_cleaner(t_temp **list, char **path2, DIR **dir)
{
	delete_list(list);
	closedir(*dir);
	free(*path2);
}
