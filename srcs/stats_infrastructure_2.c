/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_infrastructure_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:47:32 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 18:48:41 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_link_data(t_data *stats, char *buffer_inner)
{
	char	link_buf[512];
	int		count;
	int		i;

	i = 0;
	count = readlink(buffer_inner, link_buf, sizeof(link_buf));
	link_buf[count] = '\0';
	ft_memset(stats->link_name_buf, '\0', sizeof(stats->link_name_buf));
	while (link_buf[i])
	{
		stats->link_name_buf[i] = link_buf[i];
		i++;
	}
	if (ft_strequ(link_buf, buffer_inner))
	{
		ft_printf("ft_ls: %s %s\n", buffer_inner, "cyrcular link");
		exit(0);
	}
}

void	major_minor(t_data *stats, struct stat buf)
{
	if ((buf.st_mode & S_IFMT) == S_IFCHR || (buf.st_mode & S_IFMT) == S_IFBLK)
	{
		stats->major_buf = major(buf.st_rdev);
		stats->minor_buf = minor(buf.st_rdev);
	}
	else
	{
		stats->major_buf = 0;
		stats->minor_buf = 0;
	}
}
