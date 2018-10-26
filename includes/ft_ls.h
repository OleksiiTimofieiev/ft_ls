/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timofieiev <timofieiev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:18:36 by otimofie          #+#    #+#             */
/*   Updated: 2018/10/26 13:03:32 by timofieiev       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"

# include <dirent.h>
# include <sys/types.h>

typedef	struct		s_temp
{
    char			*d_name;
    unsigned char	d_type;
    struct s_temp	*next;
}					t_temp;

typedef	struct		s_qsort
{
	t_temp			*pivot;
	t_temp			*prev;
	t_temp			*tail;
	t_temp			*cur;
	t_temp			*tmp;
}					t_qsort;

void	q_sort(t_temp **headRef);
void	add(t_temp** head_ref, char *new_d_name, unsigned char d_type);
void    print_list(t_temp *list);
void	deleteList(t_temp** head_ref);

#endif
