/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:52:52 by fmeira            #+#    #+#             */
/*   Updated: 2021/10/26 01:14:27 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	init_philosopher(t_phil	*phil, t_environment *env, int i)
{
	phil->nbr = i + 1;
	phil->left_hand = false;
	phil->right_hand = false;
	phil->last_eated = 0;
	phil->times_eated = 0;
	phil->env = env;
	phil->th = NULL;
	phil->left_fork = &(phil->env->fork[phil->nbr]);
	phil->right_fork = &(phil->env->fork[phil->nbr - 1]);
	if (phil->nbr == env->nbr_philos)
	{
		phil->left_fork = &(env->fork[0]);
		phil->right_fork = &(env->fork[env->nbr_philos - 1]);
	}
	return (0);
}

static int	init_threads(t_environment	*env)
{
	int				i;

	i = 0;
	env->start_time = curr_time();
	if (pthread_mutex_init(&env->die, NULL))
		return (2);
	if (pthread_mutex_init(&env->print, NULL))
		return (2);
	while (i < env->nbr_philos)
	{
		if (pthread_mutex_init(&(env->fork[i]), NULL))
			return (2);
		i++;
	}
	i = 0;
	while (i < env->nbr_philos)
	{
		init_philosopher(&(env->phil[i]), env, i);
		if (pthread_create(&(env->phil[i].th), NULL,
				&routine, (void *)&(env->phil[i])))
			return (3);
		i++;
	}
	return (0);
}

int	init(t_environment *env, char **av)
{
	int	feedback;

	feedback = 0;
	env->no_deads = true;
	env->nbr_philos = ft_atoi(av[1]);
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	if (av[5])
		env->max_eat_times = ft_atoi(av[5]);
	else
		env->max_eat_times = -1;
	if (env->nbr_philos < 1 || env->die_time < 0 || env->eat_time < 0
		|| env->sleep_time < 0 || env->nbr_philos > 200)
		return (1);
	feedback = init_threads(env);
	return (feedback);
}
