/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_infrastructure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timofieiev <timofieiev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:38:08 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/04 11:33:54 by timofieiev       ###   ########.fr       */
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

void	get_xattr(char *type_and_permissions_buf, char *buffer_inner)
{
	char l[1024];

	type_and_permissions_buf[10] = (listxattr(buffer_inner,
		l, 1024, XATTR_SHOWCOMPRESSION)) ? '@' : ' ';
}

static void	str_copy(char *dst, char *src)
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


t_data	get_stats(char *buffer_inner)
{
	t_data		stats;
	struct stat	buf;
	char *buf1;

	stat(buffer_inner, &buf); //TODO: use lstat;
	stats.blocks_buf = buf.st_blocks;
	stats.bytes_buf = buf.st_size;
	get_file_type(stats.type_and_permissions_buf, buf.st_mode);
	get_permissions(stats.type_and_permissions_buf, buf.st_mode);
	get_xattr(stats.type_and_permissions_buf, buffer_inner);
	stats.type_and_permissions_buf[11] = '\0';
	stats.hard_links_buf = buf.st_nlink;

	// TODO: clear with char *, move ot the stack[], change names of the data structure;
	// stats.owner_name_buf = getpwuid(buf.st_uid)->pw_name;
	// stats.group_name_buf = getgrgid(buf.st_gid)->gr_name;
	stats.size_buf = buf.st_size;

	buf1 = ctime(&buf.st_mtime);;
	str_copy(stats.time_buf, buf1);

	return (stats);
}
