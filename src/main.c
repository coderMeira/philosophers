#include "../inc/philosophers.h"

int	main(int ac, char **av)
{
	t_environment	*env;

	env = NULL;
	if (ac != 5 && ac != 6)
		terminate("Wrong nbr of args");
	printf("%d\n", ac);
	//if (!(init(env, av)))
	//	terminate("Init problem");
	av++;
	return (0);
}
