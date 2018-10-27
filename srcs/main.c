#include "../includes/ft_ls.h"

#include <stdio.h>

t_data	get_stats(char *buffer)
{
	t_data	stats;

	struct stat buf;

	stat(buffer, &buf);

	stats.blocks_buf = buf.st_blocks;
	stats.bytes_buf = buf.st_size;

	return (stats);
}

void	ft_dump_cleaner(t_temp **list, char **path2, DIR **dir)
{
	delete_list(list);
	closedir(*dir);
	free(*path2);
}

void	add_slash(char ** path2)
{
	// int i = 0;
	// int flag = 0;
	size_t len = ft_strlen(*path2);

	if ((*path2)[len - 1] != '/')
	{
		ft_putstr("->>> we do not have a slash\n");
		char *tmp = ft_strdup(*path2);
		free(*path2);
		*path2 = ft_strjoin(tmp, "/");
		free(tmp);
	}

}

void	listdir(const char *name/*, int indent  flags */) // ? go from the first element of the list;
{
	DIR *dir;
	struct dirent *entry;
	t_temp *list;
	t_temp *t_list;
	char path[1024];
	char *path2 = ft_strdup(name); // make in ono init func
	char *buffer;

	add_slash(&path2);
	if (!(dir = opendir(name)))
		return ;
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
			ft_printf("\n%s\n", path);
			listdir(path);
		}
		t_list = t_list->next;
	}
	ft_dump_cleaner(&list, &path2, &dir);
}

// make it in a cycle for each command line argument;
// norminette and leaks;
// manage errors;
// validator

int		main(int argc, char **argv)
{
	(argc == 1) ? listdir(".") : listdir(argv[1]); 

	system("leaks -q ft_ls");
	
	return (0);
}


