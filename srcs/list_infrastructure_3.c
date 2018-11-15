#include "../includes/ft_ls.h"

void		add(t_temp **head_ref, char *new_d_name, t_data var)
{
	t_temp *new;
	t_temp *last;

	new = (t_temp*)malloc(sizeof(t_temp));
	last = *head_ref;
	element_constructor(new, new_d_name, var);
	if (*head_ref == NULL)
	{
		*head_ref = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void		print_date(char *time_str)
{
	int i;

	i = 4;
	while (i < 16)
		ft_printf("%c", time_str[i++]);
	ft_printf(" ");
}

void		print_dname(t_temp *list, t_flags *flags)
{
	if (list->type_and_permissions_data[0] != 'l')
	{
		if (flags->colors)
			color_printing(list);
		else
			ft_printf("%s\n", list->d_name);
	}
	else
		ft_printf("%s -> %s\n", list->d_name, list->link_name_data);
}

void		print_maj_min(t_temp *list, t_output_length *length)
{
	if (list->type_and_permissions_data[0] == 'c'
		|| list->type_and_permissions_data[0] == 'b')
		print_major_minor(list, length);
	else
		print_number_of_bytes(list, *length);
}

void		print_total(t_flags *flags, t_temp *list)
{
	if (!flags->no_total && get_total_blocks(list) != 0 && flags->long_format)
		ft_printf("total %lld\n", get_total_blocks(list));
}