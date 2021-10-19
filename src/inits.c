#include "../inc/philosophers.h"

static void	*routine(void *arg)
{
	t_phil			*phil;

	phil = (t_phil *)arg;
	printf("philo %d\n", phil->nbr);
	if (phil->nbr % 2)
		usleep(phil->env->eat_time * 1500);
	while(phil->env->no_deads)
	{
		if (!(pthread_mutex_lock(phil->left_fork) && !(pthread_mutex_lock(phil->right_fork))))
		{
			if(print_msg("has taken a fork", phil))
				return NULL;
			if(print_msg("has taken a fork", phil))
				return NULL;
			phil->left = true;
			phil->right = true;
		}
		if (phil->left && phil->right)
		{
			phil->times_eated++;
			if(print_msg("is eating", phil))
				return NULL;
			usleep(phil->env->eat_time * 1000);
			phil->last_eated = curr_time();
			pthread_mutex_unlock(phil->right_fork);
			pthread_mutex_unlock(phil->left_fork);
			if(print_msg("is sleeping", phil))
				return NULL;
			usleep(phil->env->sleep_time * 1000);
			if(print_msg("is thinking", phil))
				return NULL;
			phil->left = false;
			phil->right = false;
		}
	}
	return NULL;
}

static int	init_philosopher(t_phil	*phil, t_environment *env, int i)
{
		phil->nbr = i + 1;
		phil->left = false;
		phil->right = false;
		phil->last_eated = 0;
		phil->times_eated = 0;
		phil->env = env;
		phil->th = NULL;
		phil->left_fork = &(phil->env->fork[phil->nbr - 1]);
		phil->right_fork = &(phil->env->fork[phil->nbr]);
		if (phil->nbr == env->nbr_philos)
			phil->left_fork = &(env->fork[0]);
		return (0);
}

static int	init_threads(t_environment	*env)
{
	int				i;

	i = 0;
	env->start_time = curr_time();
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
		if (pthread_create(&(env->phil[i].th), NULL, &routine, (void *)&(env->phil[i])))
            return (3);
		i++;
	}
	return (0);
}

int	init(t_environment *env, char **av)
{
	int	err;

	err = 0;
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
	if ((err = init_threads(env)))
		return (err);
	return (0);
}
