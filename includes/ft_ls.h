/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timofieiev <timofieiev@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:18:36 by otimofie          #+#    #+#             */
/*   Updated: 2018/10/25 17:20:26 by timofieiev       ###   ########.fr       */
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
}			t_temp;

void	q_sort(t_temp **headRef);

#endif
