/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:18:36 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/11 16:20:56 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>

typedef	struct		s_temp
{
	char			*d_name;
	long long int	blocks_data;
	char			type_and_permissions_data[12];
	long int		hard_links_data;
	char			owner_name_data[20];
	char			group_name_data[20];
	long long int	size_data;
	char			time_data[20];
	int				major_data;
	int				minor_data;
	struct s_temp	*next;
}					t_temp;

typedef	struct		s_output_length
{
	int				number_of_links;
	int				owner_name;
	int				group_name;
	int				number_of_bytes;
	int				major;
	int				minor;
}					t_output_length;

typedef	struct		s_data
{
	long long	int	blocks_buf;
	char			type_and_permissions_buf[12];
	long	int		hard_links_buf;
	char			owner_name_buf[20];
	char			group_name_buf[20];
	long long int	size_buf;
	char			time_buf[20];
	int				major_buf;
	int				minor_buf;
}					t_data;

typedef	struct		s_qsort
{
	t_temp			*pivot;
	t_temp			*prev;
	t_temp			*tail;
	t_temp			*cur;
	t_temp			*tmp;
}					t_qsort;

typedef	struct		s_variables
{
	DIR				*dir;
	struct dirent	*entry;
	t_temp			*list;
	t_temp			*t_list;
	char			path[1024];
	char			*path2;
	char			*buffer;
}					t_variables;

void				q_sort(t_temp **head_ref);
void				add(t_temp **head_ref, char *new_d_name, t_data var);
void				print_list(t_temp *list);
void				delete_list(t_temp **head_ref);
void				init_path2(char **path2, char *name);
void				ft_dump_cleaner(t_temp **list, char **path2, DIR **dir);
t_data				get_stats(char *buffer);
void				str_copy(char *dst, char *src);

#endif
