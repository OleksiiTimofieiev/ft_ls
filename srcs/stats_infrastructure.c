/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_infrastructure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:38:08 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 18:48:27 by otimofie         ###   ########.fr       */
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
		type_and_permissions_buf[0] = 'p';
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

void	get_time_data(t_data *stats, struct stat buf)
{
	time_t	now;
	time_t	mtime;
	time_t	diff;
	char	*tstr;
	char	*buf1;

	now = time(NULL);
	mtime = buf.st_mtime;
	tstr = ctime(&mtime);
	diff = now - mtime;
	buf1 = ctime(&buf.st_mtime);
	str_copy(stats->time_buf, buf1);
	if ((now - 15778463) > mtime || now < mtime)
	{
		stats->time_buf[11] = ' ';
		stats->time_buf[12] = buf1[20];
		stats->time_buf[13] = buf1[21];
		stats->time_buf[14] = buf1[22];
		stats->time_buf[15] = buf1[23];
	}
}

t_data	get_stats(char *buffer_inner)
{
	t_data		stats;
	struct stat	buf;
	char		*buf1;

	lstat(buffer_inner, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFLNK)
		get_link_data(&stats, buffer_inner);
	stats.blocks_buf = (long long int)buf.st_blocks;
	get_file_type(stats.type_and_permissions_buf, buf.st_mode);
	get_permissions(stats.type_and_permissions_buf, buf.st_mode);
	get_xattr(stats.type_and_permissions_buf, buffer_inner);
	stats.type_and_permissions_buf[11] = '\0';
	stats.hard_links_buf = (long int)buf.st_nlink;
	stats.size_buf = (long long int)buf.st_size;
	buf1 = getpwuid(buf.st_uid)->pw_name;
	str_copy(stats.owner_name_buf, buf1);
	buf1 = getgrgid(buf.st_gid)->gr_name;
	str_copy(stats.group_name_buf, buf1);
	get_time_data(&stats, buf);
	major_minor(&stats, buf);
	stats.mod_time_buf = buf.st_mtime;
	return (stats);
}
