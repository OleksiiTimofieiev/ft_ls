/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 19:12:32 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 19:13:05 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		check_flags_validiry(char *str, char *invalid)
{
	while (*str)
	{
		if (*str == 'l' || *str == 'a'
			|| *str == 'r' || *str == 'R'
			|| *str == 't' || *str == 'c'
			|| *str == 'f' || *str == 'o')
			str++;
		else
		{
			*invalid = *str;
			return (0);
		}
	}
	return (1);
}

void	activate_the_flags(char *str, t_flags *flags)
{
	while (*str)
	{
		if (*str == 'l')
			flags->long_format = 1;
		else if (*str == 'a')
			flags->include_dot = 1;
		else if (*str == 'R')
			flags->recursive = 1;
		else if (*str == 'r')
			flags->reversed = 1;
		else if (*str == 't')
			flags->time_sorting = 1;
		else if (*str == 'c')
			flags->colors = 1;
		else if (*str == 'f')
			flags->freedom = 1;
		else if (*str == 'o')
			flags->no_group_user_name = 1;
		str++;
	}
}

int		set_flag_structure(char *str, t_flags *flags, char *invalid)
{
	int i;

	i = 1;
	if (!check_flags_validiry(str, invalid))
	{
		i = 0;
		return (i);
	}
	activate_the_flags(str, flags);
	return (i);
}

void	init_flags(char **argv, t_flags *flags,
				int argc, int *move_to_the_arguments)
{
	int		i;
	char	invalid;

	i = 1;
	flags->long_format = 0;
	flags->include_dot = 0;
	flags->recursive = 0;
	flags->reversed = 0;
	flags->time_sorting = 0;
	flags->no_total = 0;
	flags->freedom = 0;
	flags->no_group_user_name = 0;
	if (argc == 1)
		return ;
	while (argv[i] && argv[i][1] && argv[i][0] == '-')
	{
		if (!set_flag_structure(&argv[i][1], flags, &invalid))
		{
			ft_printf("ft_ls: illegal option -- %c\n", invalid);
			ft_printf("usage: ft_ls [-Racfolrt] [file ...]\n");
			exit(0);
		}
		*move_to_the_arguments = *move_to_the_arguments + 1;
		i++;
	}
}
