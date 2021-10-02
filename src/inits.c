#include "../inc/philosophers.h"

void timezz()
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);

}

static	void *routine(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while(phil->env->no_deads)
	{
		if (phil->nbr % 1)
			waitasec(phil->env->eat_time);
		if (phil->env->fork[phil->nbr - 1) && phil->env->fork[phil->nbr + 1))
		{
			pthread_mutex_lock(env->fork[env->phil->nbr - 1]);
			pthread_mutex_lock(env->fork[env->phil->nbr + 1]);
			eat;
			pthread_mutex_unlock(env->fork[env->phil->nbr - 1]);
			pthread_mutex_unlock(env->fork[env->phil->nbr + 1]);
		}
		else (!forks available)
			think
	}

}

static void	init_philosopher(t_phil	*phil, t_environment *env, int i)
{
		phil->nbr = i + 1;
		phil->is_eating = false;
		phil->is_thinking = true;
		phil->is_eating = false;
		phil->times_eated = 0;
		phil->env = env;
}

static int	init_threads(t_environment	*env)
{
	int	i;

	i = 0;
	while (i < env->nbr_philos)
	{
		init_philosopher(&(env->phil), env, i);
		if (pthread_mutex_init(&(env->fork[i]), NULL))
			return (1);

		if (pthread_create(env->phil[i].th, NULL, &routine, &(env->phil[i])))
            return (1);
	}
	return (0);
}

int	init(t_environment *env, char **av)
{
	env->nbr_philos = ft_atoi(av[0]);
	env->no_deads = true;
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	if (av[5])
		env->max_eat_times = ft_atoi(av[5]);
	if (init_threads(env))
		return (1);
	if (env->nbr_philos < 2 || env->die_time < 0 || env->eat_time < 0
		|| env->sleep_time < 0 || env->nbr_philos > 200)
		return (2);
}
