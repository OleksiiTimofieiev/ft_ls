/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:18:36 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/03 15:54:48 by otimofie         ###   ########.fr       */
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
	unsigned char	d_type;
	struct s_temp	*next;
	long long		bytes_data;
	long long		blocks_data;
	char			type_and_permissions_data[12];
	unsigned int	hard_links_data;
	char			*owner_name_data;
	char			*group_name_data;
	long long int	size_data;
	char 			*time_data;

}					t_temp;

typedef	struct		s_data
{
	long long		bytes_buf;
	long long		blocks_buf;
	char			type_and_permissions_buf[12];
	unsigned int	hard_links_buf;
	char			*owner_name_buf; 
	char			*group_name_buf;
	long long int	size_buf;
	char			*time_buf;

}					t_data;

typedef	struct		s_qsort
{
	t_temp			*pivot;
	t_temp			*prev;
	t_temp			*tail;
	t_temp			*cur;
	t_temp			*tmp;
}					t_qsort;

void				q_sort(t_temp **head_ref);
void				add(t_temp **head_ref, char *new_d_name,
					unsigned char d_type, t_data var/*, char *path*/);
void				print_list(t_temp *list);
void				delete_list(t_temp **head_ref);
void				init_path2(char **path2, char *name);
void				ft_dump_cleaner(t_temp **list, char **path2, DIR **dir);
t_data				get_stats(char *buffer);

#endif
