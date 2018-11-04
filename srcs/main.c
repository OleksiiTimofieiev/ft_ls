#include "../includes/ft_ls.h"

#include <stdio.h>

// global variable for the flags;

// struct options;
void	listdir(char *name/*, int indent  flags */) // ? go from the first element of the list;
{
	DIR *dir;
	struct dirent *entry;
	t_temp *list;
	t_temp *t_list;
	char path[1024];
	char *path2; // make in ono init func
	char *buffer;

	entry = NULL;
	init_path2(&path2, name);

	if (!(dir = opendir(name)))
	{
		free(path2);
		// free(buffer);
		// free(dir);

		// leak with no such file in the directory;
		ft_printf("error->>>>>>>>>>>>>>\n");

		return ;
	}

	list = NULL; // to more general func
	while ((entry = readdir(dir)) != NULL)
	{
		buffer = ft_strjoin(path2, entry->d_name);
		add(&list, entry->d_name, entry->d_type, get_stats(buffer));
		free(buffer);
	}
	q_sort(&list);
	print_list(list);
	// t_list = NULL;
	t_list = list;
	while(t_list)
	{
		if (t_list->type_and_permissions_data[0] == 'd')
		{
			if (ft_strcmp(t_list->d_name, ".") == 0 || ft_strcmp(t_list->d_name, "..") == 0)
			{
				// ft_printf("dir1 ->>>>>>>>\n");
				t_list = t_list->next;
				continue ;
			}
			// remaster snprintf;
			// ft_printf("dir2 ->>>>>>>>\n");
			snprintf(path, sizeof(path), "%s/%s", name, t_list->d_name);
			ft_printf("\n%s:\n", path); 
			listdir(path);
		}
		t_list = t_list->next;
	}
	// print_list(list);

	ft_dump_cleaner(&list, &path2, &dir);
}

// make it in a cycle for each command line argument;
// norminette and leaks;
// manage errors;
// validator;
// quantity of spaces;

int		main(int argc, char **argv)
{
	(argc == 1) ? listdir(".") : listdir(argv[1]); 

	system("leaks -q ft_ls");
	
	return (0);
}


