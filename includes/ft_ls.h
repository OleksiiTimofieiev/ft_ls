/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:18:36 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 18:53:24 by otimofie         ###   ########.fr       */
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
# include <errno.h>

typedef struct		s_flags
{
	char			long_format;
	char			include_dot;
	char			recursive;
	char			reversed;
	char			time_sorting;
	char			no_total;
	char			colors;
	char			freedom;
	char			no_group_user_name;
}					t_flags;

typedef	struct		s_temp
{
	char			*d_name;
	char			link_name_data[50];
	long long int	blocks_data;
	char			type_and_permissions_data[12];
	long int		hard_links_data;
	char			owner_name_data[20];
	char			group_name_data[20];
	long long int	size_data;
	char			time_data[20];
	int				major_data;
	int				minor_data;
	time_t			mod_time_data;
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
	time_t			mod_time_buf;
	char			link_name_buf[50];

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
void				r_q_sort(t_temp **head_ref);
void				add(t_temp **head_ref, char *new_d_name, t_data var);
void				print_list(t_temp *list, t_flags t_flags);
void				delete_list(t_temp **head_ref);
void				init_path2(char **path2, char *name);
void				ft_dump_cleaner(t_temp **list, char **path2, DIR **dir);
void				str_copy(char *dst, char *src);
t_data				get_stats(char *buffer);
void				get_link_data(t_data *stats, char *buffer_inner);
void				major_minor(t_data *stats, struct stat buf);
void				color_printing(t_temp *list);
void				print_number_of_bytes(t_temp *list, t_output_length length);
void				print_simple_params(t_temp *list, t_output_length length,
										t_flags flags);
void				print_major_minor(t_temp *list, t_output_length *length);
void				fill_the_length(t_temp *list, t_output_length *length);

#endif
