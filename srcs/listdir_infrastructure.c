/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdir_infrastructure.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 11:07:42 by otimofie          #+#    #+#             */
/*   Updated: 2018/10/28 12:15:39 by otimofie         ###   ########.fr       */
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

void	get_file_type(char *type_and_permissions_buf, mode_t file_mode)
{
	if ((file_mode & S_IFMT) == S_IFREG)
		type_and_permissions_buf[0] = '-';
	else if ((file_mode & S_IFMT) == S_IFDIR)
		type_and_permissions_buf[0] = 'd';
	else if ((file_mode & S_IFMT) == S_IFLNK)
		type_and_permissions_buf[0] = 'l';
	else if ((file_mode & S_IFMT) == S_IFCHR)
		type_and_permissions_buf[0] = 'c';
	else if ((file_mode & S_IFMT) == S_IFBLK)
		type_and_permissions_buf[0] = 'b';
	else if ((file_mode & S_IFMT) == S_IFSOCK)
		type_and_permissions_buf[0] = 'c';
	else if ((file_mode & S_IFMT) == S_IFIFO)
		type_and_permissions_buf[0] = 'f';
}

void	get_permissions(char *type_and_permissions_buf, mode_t perm_mode)
{
	type_and_permissions_buf[1] = (perm_mode & S_IRUSR) ? 'r' : '-';
	type_and_permissions_buf[2] = (perm_mode & S_IWUSR) ? 'w' : '-';
	type_and_permissions_buf[3] = (perm_mode & S_IXUSR) ? 'x' : '-';
	type_and_permissions_buf[4] = (perm_mode & S_IRGRP) ? 'r' : '-';
	type_and_permissions_buf[5] = (perm_mode & S_IWGRP) ? 'w' : '-';
	type_and_permissions_buf[6] = (perm_mode & S_IXGRP) ? 'x' : '-';
	type_and_permissions_buf[7] = (perm_mode & S_IROTH) ? 'r' : '-';
	type_and_permissions_buf[8] = (perm_mode & S_IWOTH) ? 'w' : '-';
	type_and_permissions_buf[9] = (perm_mode & S_IXOTH) ? 'x' : '-';
}

// void	get_xattr(char *type_and_permissions_buf, mode_t perm_mode)
// {
// 	type_and_permissions_buf[10] = (perm_mode & S_IRUSR) ? 'r' : '-';
// }

t_data	get_stats(char *buffer_inner)
{
	t_data stats;
	struct stat buf;

	stat(buffer_inner, &buf);

	stats.blocks_buf = buf.st_blocks;
	stats.bytes_buf = buf.st_size;

	stats.type_and_permissions_buf = ft_strnew(11);

	// copy to the list
	get_file_type(stats.type_and_permissions_buf, buf.st_mode);
	get_permissions(stats.type_and_permissions_buf, buf.st_mode);

	size_t buflen = listxattr(buffer_inner, NULL, 50, XATTR_NOFOLLOW);
	ft_printf("buflen->%d\n", buflen);
	return (stats);
}
