/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:52:39 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/25 19:52:29 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static t_bool	check_args(int ac, char **av)
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

static int	check(int i)
{
	if (i == 1)
		return (printf("Bad data provided for simulation to work properly\n"));
	if (i == 2)
		return (printf("Mutex init error\n"));
	if (i == 3)
		return (printf("Failed to init threads\n"));
	return (0);
}

static int	destroy_mutexes(t_environment *env)
{
	int	i;

	i = 0;
	while (i < env->nbr_philos)
	{
		if (pthread_mutex_destroy(&(env->fork[i])))
			return (printf("Failed to destroy forks mutexes\n"));
		i++;
	}
	if (pthread_mutex_destroy(&env->die))
		return (printf("Failed to destroy die mutex\n"));
	return (0);
}

static void	wait_for_threads(t_environment *env)
{
	int	i;

	i = 0;
	while (i < env->nbr_philos)
	{
		pthread_join(env->phil[i].th, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_environment	*env;

	env = NULL;
	if (ft_atoi(av[1]) == 1)
	{
		printf("0\t1 has taken a fork\n");
		usleep(ft_atoi(av[2]) * 1000);
		printf("%d\t1 died\n", ft_atoi(av[2]));
		return (0);
	}
	if (check_args(ac, av))
		return (-1);
	env = malloc(sizeof(t_environment));
	if (check(init(env, av)))
		return (-1);
	wait_for_threads(env);
	destroy_mutexes(env);
	free(env);
	return (0);
}
