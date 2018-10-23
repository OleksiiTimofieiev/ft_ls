#include <stdio.h>
#include <stdlib.h>

typedef		struct s_node
{
	int a;
	struct s_node *next;
}					t_node;

void	recursion_test(void)
{
	t_node *ptr = NULL;
	
	static int sum = 0;

	if (sum < 3)
	{
		if (!ptr)
		{
			ptr = (t_node*)malloc(sizeof(t_node*));
			ptr->a = sum;
			printf("NULL\n");
			printf("%d\n", ptr->a);
			ptr->next = (t_node*)malloc(sizeof(t_node*));
			ptr->next->a = 7;
			printf("%d\n", ptr->next->a);

			sum++;
			
		}
		else
			printf("Not NULL\n");
	}
	else
		return ;

	recursion_test();


}

int		main(void)
{
	int quantity_of_nodes = 2;
	recursion_test();


	return 0;
}