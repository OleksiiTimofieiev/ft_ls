/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_infrastructure_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:51:28 by otimofie          #+#    #+#             */
/*   Updated: 2018/11/15 18:51:58 by otimofie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	fill_the_length(t_temp *list, t_output_length *length)
{
	length->number_of_links = ft_decimal_length(list->hard_links_data);
	length->owner_name = ft_strlen(list->owner_name_data);
	length->group_name = ft_strlen(list->group_name_data);
	length->number_of_bytes = ft_decimal_length(list->size_data);
	length->major = ft_decimal_length(list->major_data);
	length->minor = ft_decimal_length(list->minor_data);
	while (list)
	{
		if (length->number_of_links < ft_decimal_length(list->hard_links_data))
			length->number_of_links = ft_decimal_length(list->hard_links_data);
		if (length->owner_name < (int)ft_strlen(list->owner_name_data))
			length->owner_name = (int)ft_strlen(list->owner_name_data);
		if (length->group_name < (int)ft_strlen(list->group_name_data))
			length->group_name = (int)ft_strlen(list->group_name_data);
		if (length->number_of_bytes < ft_decimal_length(list->size_data))
			length->number_of_bytes = ft_decimal_length(list->size_data);
		if (length->major != 0 && length->major <
										ft_decimal_length(list->major_data))
			length->major = ft_decimal_length(list->major_data);
		if (length->minor != 0 && length->minor <
										ft_decimal_length(list->minor_data))
			length->minor = ft_decimal_length(list->minor_data);
		list = list->next;
	}
}

void	print_major_minor(t_temp *list, t_output_length *length)
{
	ft_printf("%s", " ");
	if (list->major_data != 0)
		ft_printf("%*d, ", length->major, list->major_data);
	else
		ft_printf("%*d, ", length->major - 1, list->major_data);
	if (list->minor_data > 255)
		ft_printf("%#010x", list->minor_data);
	else if (list->minor_data != 0)
		ft_printf("%*d", length->minor, list->minor_data);
	else
		ft_printf("%*d", length->minor - 1, list->minor_data);
	ft_putchar(32);
}

void	print_simple_params(t_temp *list, t_output_length length,
							t_flags flags)
{
	ft_printf("%s ", list->type_and_permissions_data);
	ft_printf("%*d ", length.number_of_links, list->hard_links_data);
	if (flags.no_group_user_name != 1)
	{
		ft_printf("%*-s", length.owner_name + 2, list->owner_name_data);
		ft_printf("%*-s", length.group_name + 2, list->group_name_data);
	}
}

void	print_number_of_bytes(t_temp *list, t_output_length length)
{
	if (list->size_data)
		ft_printf("%*lld ", length.number_of_bytes,
					(long long)list->size_data);
	else
		ft_printf("%*lld ", length.number_of_bytes - 1,
					(long long)list->size_data);
}

void	color_printing(t_temp *list)
{
	if (list->type_and_permissions_data[0] == 'd')
		ft_printf("%s%s%s\n", GREEN, list->d_name, RESET);
	else if (list->type_and_permissions_data[0] == '-')
		ft_printf("%s%s%s\n", CYAN, list->d_name, RESET);
	else if (list->type_and_permissions_data[0] == 'b')
		ft_printf("%s%s%s\n", RED, list->d_name, RESET);
	else if (list->type_and_permissions_data[0] == 'c')
		ft_printf("%s%s%s\n", RED, list->d_name, RESET);
	else if (list->type_and_permissions_data[0] == 'p')
		ft_printf("%s%s%s\n", MAGENTA, list->d_name, RESET);
	else
		ft_printf("%s\n", list->d_name);
}
