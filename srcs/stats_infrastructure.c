/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_infrastructure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:38:08 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/04 21:14:41 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
		type_and_permissions_buf[0] = 's';
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

void	get_xattr(char *type_and_permissions_buf, char *buffer_inner)
{
	char l[2024];

	type_and_permissions_buf[10] = (listxattr(buffer_inner,
		l, 2024, XATTR_NOFOLLOW) > 0) ? '@' : ' ';
}

t_data	get_stats(char *buffer_inner)
{
	t_data		stats;
	struct stat	buf;
	char		*buf1;

	lstat(buffer_inner, &buf);
	stats.blocks_buf = buf.st_blocks;
	stats.bytes_buf = buf.st_size;
	get_file_type(stats.type_and_permissions_buf, buf.st_mode);
	get_permissions(stats.type_and_permissions_buf, buf.st_mode);
	get_xattr(stats.type_and_permissions_buf, buffer_inner);
	stats.type_and_permissions_buf[11] = '\0';
	stats.hard_links_buf = buf.st_nlink;
	stats.size_buf = buf.st_size;
	buf1 = getpwuid(buf.st_uid)->pw_name;
	str_copy(stats.owner_name_buf, buf1);
	buf1 = getgrgid(buf.st_gid)->gr_name;
	str_copy(stats.group_name_buf, buf1);
	buf1 = ctime(&buf.st_mtime);;
	str_copy(stats.time_buf, buf1);
	if ((buf.st_mode & S_IFMT) == S_IFCHR) // major / minor // TODO: get all clear;
	{
		ft_printf("MAJOR-> %d ", major(buf.st_rdev));
		ft_printf("MINOR -> %d\n", minor(buf.st_rdev));
	}
	return (stats);
}
