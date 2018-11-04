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

	init_path2(&path2, name);
	if (!(dir = opendir(name)))
	{
		// free(path2);
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
	q_sort(&list);	// ? q_sort in print list;
	print_list(list); // ? q_sort in print list;	// handle size of printing;
	t_list = list;
	while(t_list)
	{
		if (t_list->d_type == DT_DIR)
		{
			if (ft_strcmp(t_list->d_name, ".") == 0 || ft_strcmp(t_list->d_name, "..") == 0)
			{
				t_list = t_list->next;
				continue ;
			}
			// remaster snprintf;
			snprintf(path, sizeof(path), "%s/%s", name, t_list->d_name);
			ft_printf("\n%s:\n", path); 
			listdir(path);
		}
		t_list = t_list->next;
	}
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


