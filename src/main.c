#include "../inc/philosophers.h"

static	t_bool	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Wrong nbr of args\n");
		return (1);
	}
	while (av[i])
	{
		if (not_int(av[i++]))
		{
			printf("All args should be numbers\n");
			return (1);
		}
	}
	return (0);
}

static	t_bool check(int i)
{
	if (i == 1)
		return (printf("Failed to init threads"));
	if (i == 2)
		return (printf("Bad data provided for simulation to work properly"));
	if (i == 3)
		return (printf("mutex init error\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_environment	*env;
	t_phil			**phils;

	phils = NULL;
	if (check_args(ac, av))
		return (-1);
	env = malloc(sizeof(t_environment));
	if (check(init(env, av, phils)))
		return (-1);
	//	terminate("Init problem");
	av++;
	return (0);
}
