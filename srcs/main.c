#include "../includes/ft_ls.h"

#include <stdio.h> // for snprintf;

//  - major / minor in the necessary format (first and second part) <-> print separately;
//  - ls with link and a directory; dev vs dev/
//  - output format;
// make it in a cycle for each command line argument;
// norminette and leaks;
// manage errors;
// validator;
// quantity of spaces;
// ls -laRrt
// ls -l -a -r -t ...
// work with errors from Liubomir
// think over about the all flags
// redo snprintf;
// dif print modef for the different file types;
// hex in dev;

// flags = // struct options;

// chmod 000 -> no rights
// not exists

// etc
// etc/
// tmp
// tmp/
// dev
// dev/

// ➜  ft_ls git:(master) ✗ ls -laR /etc
// lrwxr-xr-x@ 1 root  wheel  11 Mar  4  2018 /etc -> private/etc

// ➜  ft_ls git:(master) ✗ ls -la LinkDir
// lrwxr-xr-x  1 otimofie  2017  3 Nov  3 15:01 LinkDir -> Dir
// ➜  ft_ls git:(master) ✗ ls -la LinkDir/
// total 0
// drwxr-xr-x   2 otimofie  2017    68 Nov  3 15:01 .
// drwxr-xr-x  36 otimofie  2017  1224 Nov  4 15:47 ..

// b and c file types
// link -> dir, hindu has the solution

//TODO: modify with * according to the biggest length;

// 'p' instead of 'f' in /etc/

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
	if (!(dir = opendir(name))) // separate func;
	{
		free(path2);
		// free(buffer);
		// free(dir);

		// leak with no such file in the directory;
		ft_printf("error->>>>>>>>>>>>>>\n");
		perror("open");

		return ;
	}

	list = NULL; // to more general func // add to func above;
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

int		main(int argc, char **argv)
{
	(argc == 1) ? listdir(".") : listdir(argv[1]); 
	system("leaks -q ft_ls");
	return (0);
}


